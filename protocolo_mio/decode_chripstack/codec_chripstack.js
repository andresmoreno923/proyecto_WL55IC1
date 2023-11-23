// Decode uplink function.
//
// Input is an object with the following fields:
// - bytes = Byte array containing the uplink payload, e.g. [255, 230, 255, 0]
// - fPort = Uplink fPort.
// - variables = Object containing the configured device variables.
//
// Output must be an object with the following fields:
// - data = Object representing the decoded payload.

class tlv {
    constructor(msg) {
        this.msg = msg;
        this.n = msg.length;
        this.group_b10 = new Array(Math.floor(this.n / 2));
        this.group_b16 = [];
        this.data_marks = ["24", "09", "0A", "0B", "0C", "0D", "0E", "0F", "16", "19", "1B", "1C", "1F", "22"];
        this.length_dm = [1, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 6, 2, 2];
        this.cs = 0;
        this.ind = 0;
        this.i = 0;

        this.meter_n = 0;
        this.ax = 0;
        this.ay = 0;
        this.az = 0;
        this.tmp102 = 0;
        this.bme280_t = 0;
        this.bme280_h = 0;
        this.bme280_p = 0;
        this.meter_t = "";
        this.year = 0;
        this.month = 0;
        this.day = 0;
        this.hour = 0;
        this.min = 0;
        this.sec = 0;
        
        this.json = {};
    }

    split_str() {
        if (this.msg.length % 2 !== 0) {
            this.msg += ' ';
            this.n = this.msg.length;
        }
        let j = 0;
        for (let i = 0; i < this.n - 1; i += 2) {
            this.group_b16.push(this.msg.slice(i, i + 2));
            this.group_b10[j] = parseInt(this.msg.slice(i, i + 2), 16);
            //console.log(j, this.msg.slice(i, i + 2));
            j++;
        }

        
    }

    cs_rec() {
        const num_ = this.group_b10.slice(0, -1).reduce((acc, val) => acc + val, 0);
        const sum_ = (num_ > 255 ? num_.toString(16).slice(3) : num_.toString(16)).toUpperCase().padStart(2, '0');
        this.cs = this.group_b16.slice(-1)[0] === sum_ ? 1 : 0;
        return this.cs;
    }

    decode() {
        this.i = 0;
        this.ind = 0;

        while (this.i < this.group_b16.length - 1) {
            
            this.ind = this.length_dm[this.data_marks.indexOf(this.group_b16[this.i])];
            //console.log(this.group_b16[this.i], this.i, this.ind);
            //console.log(typeof this.group_b16[this.i]);
            
            switch (this.group_b16[this.i]) {
                case "09":
                     this.decode_acc_x();
                     break;
                case "0A":
                    this.decode_acc_y();
                    break;
                case "0B":
                     this.decode_acc_z();
                     break;
                case "0C":
                     this.decode_tmp102();
                     break;
                case "0D":
                     this.decode_bme280_t();
                     break;
                case "0E":
                     this.decode_bme280_h();
                     break;
                case "0F":
                     this.decode_bme280_p();
                     break;
                case "16":
                     this.decode_meter_n();
                     break;
                case "1B":
                     this.decode_meter_t();
                     break;
                case "1C":
                     this.decode_date_time();
                     break;
                case "22":
                     this.decode_error_st();
                     break;
            }
            
            
            if(this.i == 0)
            {
                this.i = this.i + this.ind;
            }else{
                this.i = this.i + this.ind + 1;
            }
           
        }
        return this.json;
    }

    decode_acc_x() {
        this.ax = parseInt(this.group_b16.slice(this.i + 1, this.i + this.ind + 1).join(''), 16) / 16384.0;
        this.json.ax = this.ax;
    }

    decode_acc_y() {
        this.ay = parseInt(this.group_b16.slice(this.i + 1, this.i + this.ind + 1).join(''), 16) / 16384.0;
        this.json.ay = this.ay;
    }

    decode_acc_z() {
        this.az = parseInt(this.group_b16.slice(this.i + 1, this.i + this.ind + 1).join(''), 16) / 16384.0;
        this.json.az = this.az;
    }

    decode_tmp102() {
        this.tmp102 = 0.0625 * parseInt(this.group_b16.slice(this.i + 1, this.i + this.ind + 1).join(''), 16);
        this.json.tmp102 = this.tmp102;
    }

    decode_bme280_t() {
        this.bme280_t = 0.0625 * parseInt(this.group_b16.slice(this.i + 1, this.i + this.ind + 1).join(''), 16);
        this.json.bme280_t = this.bme280_t;
    }

    decode_bme280_h() {
        this.bme280_h = 0.0625 * parseInt(this.group_b16.slice(this.i + 1, this.i + this.ind + 1).join(''), 16);
        this.json.bme280_h = this.bme280_h;
    }

    decode_bme280_p() {
        this.bme280_p = 0.0625 * parseInt(this.group_b16.slice(this.i + 1, this.i + this.ind + 1).join(''), 16);
        this.json.bme280_p = this.bme280_p;
    }

    decode_meter_n() {
        this.meter_n = parseInt(this.group_b16.slice(this.i + 1, this.i + this.ind + 1).join(''), 16);
        this.json.meter_n = this.meter_n;
    }

    decode_meter_t() {
        this.meter_t = this.group_b16.slice(this.i + 1, this.i + this.ind + 1).join('');
        this.json.meter_t = this.meter_t;
    }

    decode_date_time() {
        const temp = this.group_b16.slice(this.i + 1, this.i + this.ind + 1).join('');
        this.year = parseInt(temp.slice(0, 2), 16);
        this.month = parseInt(temp.slice(2, 4), 16);
        this.day = parseInt(temp.slice(4, 6), 16);
        this.hour = parseInt(temp.slice(6, 8), 16);
        this.min = parseInt(temp.slice(8, 10), 16);
        this.sec = parseInt(temp.slice(10, 12), 16);
        
        this.json.year = this.year;
        this.json.month = this.month;
        this.json.day = this.day;
        this.json.hour = this.hour;
        this.json.min = this.min;
        this.json.sec = this.sec;
    }

    decode_error_st() {
        const temp = this.group_b16.slice(this.i + 1, this.i + this.ind + 1).join('');
        this.error_sensor_id(temp.slice(0, 2));
        this.error_code(temp.slice(2));
    }

 
    error_sensor_id(id) {
        const idError = {
            '30': 'No sensor Error',
            '31': 'mpu6050',
            '32': 'tmp102',
            '33': 'bme280',
            '34': 'gps'
        };
        this.json.error_sensor_id = idError[id];
        
    }

    error_code(id) {
        const errorType = {
            '40': 'No error',
            '41': 'No Device',
            '42': 'No Data',
            '43': 'Invalid Gps Data'
        };
        this.json.error_type = errorType[id];
    }
}

function decodeUplink(input) {
   var buffer = input.bytes;
   var data = {};
   var shortHeader = (buffer[0] & 0xFF);

  	//parsed = prueba(parsed, buffer);
  	//parsed.msg = buffer[0];
  
  let numeroAleatorio = Math.random();
  var inputString1;
  
  if(numeroAleatorio<0.5){
    inputString1 = "24191616123456781C1303010000001B0109000003EC22314158";
  }else{
    inputString1 = "241916161234567858";
  }

  const instanciaTlv = new tlv(inputString1);

  // Llamar a los métodos necesarios para procesar la entrada
  instanciaTlv.split_str();
  instanciaTlv.cs_rec();
  data = instanciaTlv.decode();
  
  return {
    data,
  };
  
}

// Encode downlink function.
//
// Input is an object with the following fields:
// - data = Object representing the payload that must be encoded.
// - variables = Object containing the configured device variables.
//
// Output must be an object with the following fields:
// - bytes = Byte array containing the downlink payload.
function encodeDownlink(input) {
  return {
    bytes: [225, 230, 255, 0]
  };
}
