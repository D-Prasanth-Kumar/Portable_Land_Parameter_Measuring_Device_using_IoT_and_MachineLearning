import pandas as pd
import joblib
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestClassifier

# Load the dataset
df = pd.read_csv("Soil_Parameter_ML_Dataset_200.csv")

# print("First few rows of the dataset: ")
# print(df.head()

# Splitting input features and outputs 

# Predicting pH, EC, soil type and crop
# inputs
X = df[['soil_moisture', 'ambient_temp', 'humidity', 'soil_temp']]

# Outputs to predict
y_ph = df['pH']
y_ec = df['EC']
y_soil_type = df['soil_type']
y_crop = df['suitable_crop']

# Train regression models
ph_model = LinearRegression()
ec_model = LinearRegression()

ph_model.fit(X, y_ph)
ec_model.fit(X, y_ec)

joblib.dump(ph_model, 'pH_model.pkl')
joblib.dump(ec_model, 'EC_model.pkl')

# Train classification models for soil type and crop
soil_type_model = RandomForestClassifier()
crop_model = RandomForestClassifier()

soil_type_model.fit(X, y_soil_type)
crop_model.fit(X, y_crop)

joblib.dump(soil_type_model, 'soil_type_model.pkl')
joblib.dump(crop_model, 'crop_model.pkl')

# example input (test data)
sample_input = [[45, 30, 70, 28]]
            #     M  A-T  H  S-T

predicted_ph = ph_model.predict(sample_input)[0]
predicted_ec = ec_model.predict(sample_input)[0]
predicted_soil_type = soil_type_model.predict(sample_input)[0]
predicted_crop = crop_model.predict(sample_input)[0]


print("Predicted Result: ")
print(f"pH Value: {predicted_ph:.2f}")
print(f"EC: {predicted_ec:.2f}")
print(f"Soil Type: {predicted_soil_type}")
print(f"Suitable Crop: {predicted_crop}")