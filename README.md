# Air Quality Monitoring Task Using LinkIt One Board

Goals:
1. Collect air quality data through the use of LinkIt One (MT2502A) with the help of SGX VZ89TE I2C sensor.
	* LinkIt One Board: https://www.seeedstudio.com/LinkIt-ONE-p-2017.html
	* Sensor: https://sgx.cdistore.com/products/detail/micsvz89te-sgx-sensortech/598202/

2. Publishing the collected data to a MQTT Broker for visualization purposes.
	* MQTT Broker Website: https://thingsboard.io
	* MQTT Broker LogIn Page: http://demo.thingsboard.io/login

# Requirements
1. Mediatek LinkIt One board

2. Well soldered SGX VZ89TE I2C sensor so as to connect to the LinkIt One board

3. Arduino IDE
	* MacOS: https://docs.labs.mediatek.com/resource/linkit-one/en/getting-started/get-started-on-os-x
	* Windows: https://docs.labs.mediatek.com/resource/linkit-one/en/getting-started/get-started-on-windows

4. Necessary Libraries

5. MQTT broker (Whichever Platform You Find Useful)

6. Internet Connection

# Things we did but not covered here:
1. Soldering the board

2. Steps for setting up visualization dashboards and credential setup. However you can get the necessary information from:
	* Devices: https://thingsboard.io/docs/user-guide/ui/devices/
	* Dashboards: https://thingsboard.io/docs/user-guide/ui/dashboards/

# Authors:
* Eric Dereck Ochaka
* Ondrej Gadjgusek
* Sarka Chwastkova (https://github.com/sarkaaa)
* Ramin Madani
* Gaétan Porchet 
* Nikolai Grigorjev

Special thanks to all who contributed in all ways possible.
