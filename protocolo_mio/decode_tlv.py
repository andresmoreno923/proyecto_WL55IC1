# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import numpy as np
import json

class tlv():
    def __init__(self, msg):
        self.msg = msg
        self.n = len(msg)
        self.group_b10 = np.zeros(int(self.n/2))
        self.group_b16 = []
        self.data_marks = ["24","09","0A","0B","0C", "0D", "0E","0F", "16", "19", "1B", "1C", "1F", "22"]
        self.length_dm = [1,4,4,4,4,4,4,4,4,1,1,6,2,2]
        self.cs = 0
        self.ind = 0
        self.i = 0
        
        self.meter_n = 0
        self.ax = 0
        self.ay = 0
        self.az = 0
        self.tmp102 = 0
        self.bme280_t = 0
        self.bme280_h = 0
        self.bme280_p = 0
        self.meter_t = ""
        self.year = 0
        self.month = 0
        self.day = 0
        self.hour = 0
        self.min = 0
        self.sec = 0
        
        
        
    def split_str(self):
        
        if len(self.msg) % 2 != 0:
            self.msg += ' '
            self.n = len(self.msg)
        j = 0
        for i in range(0, self.n-1,2):
            self.group_b16.append(self.msg[i:i+2])
            self.group_b10[j] = int(self.msg[i:i+2],16)
            j += 1

    def cs_rec(self):
        num_ = int(np.sum(self.group_b10[:-1]))
        sum_ = hex(num_)[3 if num_>255 else 2:].zfill(2).upper()
        self.cs = 1 if (self.group_b16[-1]==sum_) else 0
        
        return self.cs
    
    def decode(self):
        
        #for i in range(0, len(self.group_b16)):
        self.i = 0
        self.ind = 0
        while( self.i<len(self.group_b16)-1 ):
            self.ind = self.length_dm[self.data_marks.index(self.group_b16[self.i])]
            self.switch_case( self.group_b16[self.i] )
            self.i = (self.i+self.ind) if (self.i==0) else (self.i+self.ind+1)
            
             
            
            #print( i, ind,self.group_b16[i], self.length_dm[ind] )
            #break
                

    def decode_acc_x(self):
        self.ax =int(''.join(self.group_b16[self.i +1: self.i + self.ind +1]),16)/16384.0
        print("ax: ",self.ax)
    
    def decode_acc_y(self):
        self.ay =int(''.join(self.group_b16[self.i +1: self.i + self.ind +1]),16)/16384.0
        print("ay: ",self.ay)
    
    def decode_acc_z(self):
        self.az =int(''.join(self.group_b16[self.i +1: self.i + self.ind +1]),16)/16384.0
        print("az: ",self.az)

    def decode_tmp102(self):
        self.tmp102 =0.0625*int(''.join(self.group_b16[self.i +1: self.i + self.ind +1]),16)
        print("tmp102: ",self.tmp102)
    
    def decode_bme280_t(self):
        self.bme280_t =0.0625*int(''.join(self.group_b16[self.i +1: self.i + self.ind +1]),16)
        print("bme280_t: ",self.bme280_t2)
    
    def decode_bme280_h(self):
        self.bme280_h =0.0625*int(''.join(self.group_b16[self.i +1: self.i + self.ind +1]),16)
        print("bme280_h: ",self.bme280_h)
    
    def decode_bme280_p(self):
       self.bme280_p =0.0625*int(''.join(self.group_b16[self.i +1: self.i + self.ind +1]),16)
       print("bme280_p: ",self.bme280_p)
    
    def decode_meter_n(self):
        self.meter_n =int(''.join(self.group_b16[self.i +1: self.i + self.ind +1]),16)  
        print("meter no: ", self.meter_n)
        pass
    
    def decode_meter_t(self):
        self.meter_t =''.join(self.group_b16[self.i +1: self.i + self.ind +1])
        print("meter t: ", self.meter_t)
        pass
    
    def decode_date_time(self):
        
        temp =''.join(self.group_b16[self.i +1: self.i + self.ind +1])
        self.year = int( temp[0:2] ,16)
        self.month = int( temp[2:4] ,16)
        self.day = int( temp[4:6] ,16)
        
        self.hour = int( temp[6:8] ,16)
        self.min = int( temp[8:10] ,16)
        self.sec = int( temp[10:12] ,16)
        
        print("fecha(AA/MM/DD): ",self.year, self.month, self.day)
        print("hora: ",self.hour, self.min, self.sec)

    
    def decode_error_st(self):
        
        temp =''.join(self.group_b16[self.i +1: self.i + self.ind +1])
        self.error_sensor_id(temp[:2])
        self.error_code(temp[2:])
        
    
    def default(self):
        pass
    
    def switch_case(self,case):
        switch_dict = {
            "09": self.decode_acc_x,
            "0A": self.decode_acc_y,
            "0B": self.decode_acc_z,
            "0C": self.decode_tmp102,
            "0D": self.decode_bme280_t,
            "0E": self.decode_bme280_h,
            "0F": self.decode_bme280_p,
            "16": self.decode_meter_n,
            "1B": self.decode_meter_t,
            "1C": self.decode_date_time,
            "22": self.decode_error_st,
        }
        return switch_dict.get(case, self.default)()
    
    def error_sensor_id(self, id):
        id_error = {
            '30': 'No sensor Error',
            '31': 'mpu6050',
            '32': 'tmp102',
            '33': 'bme280',
            '34': 'gps'
        }
        print("id:",id,"sensor type:",id_error[id])
        
    def error_code(self, id):
        error_type = {
            '40': 'No error',
            '41': 'No Device',
            '42': 'No Data',
            '43': 'Invalid Gps Data'
        }
        print("id:",id,"error type:",error_type[id])
    
    def to_json(self, archivo="datos.json"):
        # Crear un diccionario con los datos de la instancia
        datos_dict = {
            "meter_n": self.meter_n,
            "ax": self.ax,
            "ay": self.ay,
            "az": self.az,
            "tmp102": self.tmp102,
            "bme280_t": self.bme280_t,
            "bme280_h": self.bme280_h,
            "bme280_p": self.bme280_p,
            "meter_t": self.meter_t,
            "year": self.year,
            "month": self.month,
            "day": self.day,
            "hour": self.hour,
            "min": self.min,
            "sec": self.sec
        }

        # Convertir el diccionario a JSON
        datos_json = json.dumps(datos_dict, indent=2)

        # Escribir el JSON en un archivo
        with open(archivo, 'w') as file:
            file.write(datos_json)


      

string = "24191616123456781C1303010000001B0109000003EC22314158"

print("mensaje recibido: ", string)
print("\nmensaje decodificado\n")
decodificador = tlv(string)
decodificador.split_str()
decodificador.cs_rec()
decodificador.decode()

decodificador.to_json("datos_guardados.json")

