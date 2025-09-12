async function fetchData() {
  try {
    const response = await fetch("https://Prasanth23.pythonanywhere.com/latest");
    const data = await response.json();

    document.getElementById("moisture").innerText = data.soil_moisture;
    document.getElementById("temperature").innerText = data.ambient_temp + " °C";
    document.getElementById("humidity").innerText = data.humidity + " %";
    document.getElementById("soil_temp").innerText = data.soil_temp + " °C";

    document.getElementById("ph").innerText = data.pH;
    document.getElementById("ec").innerText = data.EC;
    document.getElementById("soil_type").innerText = data.soil_type;
    document.getElementById("crop").innerText = data.suitable_crop;
  } catch (err) {
    console.error("Error fetching data:", err);
  }
}

setInterval(fetchData, 10000);
fetchData();
