from flask import Flask, request, jsonify
from flask_cors import CORS
import joblib
import numpy as np
import pandas as pd
import os

# Start Flask app
app = Flask(__name__)
CORS(app)

# Load trained models
ph_model = joblib.load('pH_model.pkl')
ec_model = joblib.load('EC_model.pkl')
soil_type_model = joblib.load('soil_type_model.pkl')
crop_model = joblib.load('crop_model.pkl')

# Global dictionary to store last prediction
latest_data = {}

# Path to live log CSV file
LOG_FILE = "live_data_log.csv"

@app.route('/predict', methods=['POST'])
def predict():
    global latest_data
    data = request.get_json()

    try:
        # Extract input sensor values
        soil_moisture = float(data['soil_moisture'])
        ambient_temp = float(data['ambient_temp'])
        humidity = float(data['humidity'])
        soil_temp = float(data['soil_temp'])

        input_data = [[soil_moisture, ambient_temp, humidity, soil_temp]]

        # Predict
        pH = ph_model.predict(input_data)[0]
        EC = ec_model.predict(input_data)[0]
        soil_type = soil_type_model.predict(input_data)[0]
        crop = crop_model.predict(input_data)[0]

        latest_data = {
            'soil_moisture': soil_moisture,
            'ambient_temp': ambient_temp,
            'humidity': humidity,
            'soil_temp': soil_temp,
            'pH': round(pH, 2),
            'EC': round(EC, 2),
            'soil_type': soil_type,
            'suitable_crop': crop
        }

        # ---- Logging part ----
        df_log = pd.DataFrame([latest_data])
        if os.path.exists(LOG_FILE):
            df_log.to_csv(LOG_FILE, mode='a', header=False, index=False)
        else:
            df_log.to_csv(LOG_FILE, index=False)

        return jsonify(latest_data)

    except Exception as e:
        return jsonify({'error': str(e)})

@app.route('/latest', methods=['GET'])
def get_latest():
    if latest_data:
        return jsonify(latest_data)
    else:
        return jsonify({'message': 'No data received yet'}), 404

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
