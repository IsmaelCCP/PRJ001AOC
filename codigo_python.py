#!/usr/bin/python3

import serial
import sys
import psycopg2
import time


def sistema():
    try:
        ser = serial.Serial('/dev/ttyACM0', 9600, timeout=0)
        conn = psycopg2.connect(host='localhost', database='banco', user='postgres', password='root')
        if conn:
            print("Conexão efetuada com sucesso")

            cur = conn.cursor()
            cur.execute("SELECT id, comando FROM tb_aoc WHERE situacao=1 ORDER BY id ASC")
            rows = cur.fetchall()
            for row in rows:
                id = row[0]
                dadoEnviar = row[1]
                ser.write(dadoEnviar.encode())
                time.sleep(0.05)
                dadoRecebido = ser.readline()
                cur.execute("UPDATE tb_aoc set retorno=%s, situacao=0 WHERE id=%d", (dadoRecebido, id))
                conn.commit()
    except:
        print("Erro: {}".format(sys.exc_info()[0]))
        time.sleep(2)


def main(argv):
    while True:
        sistema()
    pass


if __name__ == "__main__":
    main(sys.argv)
