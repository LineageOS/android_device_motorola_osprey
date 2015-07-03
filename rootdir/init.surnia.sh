#!/system/bin/sh
PATH=/system/bin

product_model=`getprop ro.product.model`

if [ "XT1527" = $product_model ]; then
	log -t$TAG "Applying LTE fix"
	setprop ro.cdma.home.operator.numeric 311870
	setprop ro.cdma.home.operator.alpha "Boost Mobile"
	setprop ro.product.locale.region US
	setprop gsm.sim.operator.alpha "Boost Mobile"
	setprop gsm.sim.operator.numeric 311870
	setprop gsm.operator.alpha "Boost Mobile"
	setprop gsm.operator.numeric 311870
	setprop gsm.sim.operator.iso-country US
	setprop gsm.operator.iso-country US
	setprop ro.telephony.default_network 8
	#Now copy the eri.xml to /data/eri.xml
	cp /system/etc/boost/eri.xml /data/eri.xml
fi

