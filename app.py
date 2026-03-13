from flask import Flask, request, jsonify
import pymysql
from datetime import datetime

app = Flask(__name__)

def get_db():
    return pymysql.connect(
        host="localhost",
        user="root",
        password="YOUR_DB_PASSWORD",
        database="sensor_data",
        charset="utf8"
    )

@app.route('/data', methods=['POST','GET'])
def sensor_data():

    db = get_db()
    cursor = db.cursor()

    if request.method == 'POST':

        data = request.form.get('data')
        print("Received:", data)

        if data:

            values = data.split(",")

            humidity = float(values[0])
            temperature = float(values[1])
            ldr = values[2]
            moisture = int(values[3])

            now = datetime.now()
            date = now.strftime("%Y-%m-%d")
            time = now.strftime("%H:%M:%S")

            sql = """INSERT INTO readings
                     (humidity, temperature, ldr, moisture, date, time)
                     VALUES (%s,%s,%s,%s,%s,%s)"""

            val = (humidity, temperature, ldr, moisture, date, time)

            cursor.execute(sql, val)
            db.commit()

            cursor.close()
            db.close()

            return "Data Stored"

        return "No Data"

    if request.method == 'GET':

        cursor.execute("SELECT * FROM readings ORDER BY id DESC LIMIT 1")
        row = cursor.fetchone()

        cursor.close()
        db.close()

        if row:
            return jsonify({
                "id": row[0],
                "humidity": row[1],
                "temperature": row[2],
                "ldr": row[3],
                "moisture": row[4],
                "date": str(row[5]),
                "time": str(row[6])
            })

        return jsonify({"message":"No Data"})


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
