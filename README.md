# Air Quality Monitoring Task Using LinkIt One Board

Goals:
1. Collect air quality data through the use of LinkIt One (MT2502A) with the help of SGX VZ89TE I2C sensor.

LinkIt One Board: https://www.seeedstudio.com/LinkIt-ONE-p-2017.html
Sensor: https://sgx.cdistore.com/products/detail/micsvz89te-sgx-sensortech/598202/

2. Publishing the collected data to a MQTT Broker for visualization purposes.
MQTT Broker Website: https://thingsboard.io
MQTT Broker LogIn Page: http://demo.thingsboard.io/login

Things we did but not covered here:
1. Soldering the board
2. Steps for setting up visualization dashboards and credential setup. However you can get the necessary information from:
	a. Devices: https://thingsboard.io/docs/user-guide/ui/devices/
	b. Dashboards: https://thingsboard.io/docs/user-guide/ui/dashboards/

Special thanks to all who contributed in all ways possible.

Authors:
Eric Dereck Ochaka
Ondrej Gadjgusek
Sarka Chwastkova
Ramin Madani
Gaétan Porchet 
Nikolai Grigorjev

Air quality monitoring code for LinkIt One (MT2502A) and pushing the readings to thingsboard cloud platform.
