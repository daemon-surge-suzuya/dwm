battery() {
	pwr=$(cat /sys/class/power_supply/BAT0/capacity);
	sts=$(cat /sys/class/power_supply/BAT0/status);	icon=""
	if [ "$pwr" -ge 90 ]; then icon="󰁹";
	elif [ "$pwr" -lt 90 ] && [ "$pwr" -ge 80 ]; then icon="󰂂";
	elif [ "$pwr" -lt 80 ] && [ "$pwr" -ge 70 ]; then icon="󰂁";
	elif [ "$pwr" -lt 70 ] && [ "$pwr" -ge 60 ]; then icon="󰂀";
	elif [ "$pwr" -lt 60 ] && [ "$pwr" -ge 50 ]; then icon="󰁿";
	elif [ "$pwr" -lt 50 ] && [ "$pwr" -ge 40 ]; then icon="󰁾";
	elif [ "$pwr" -lt 40 ] && [ "$pwr" -ge 30 ]; then icon="󰁽";
	elif [ "$pwr" -lt 30 ] && [ "$pwr" -ge 20 ]; then icon="󰁼";
	elif [ "$pwr" -lt 20 ] && [ "$pwr" -ge 10 ]; then icon="󰁻";
	elif [ "$pwr" -lt 10 ] && [ "$pwr" -ge 0 ];  then icon="󰁺";
	fi	
	case "$sts" in
		"Charging") pwr="+$pwr%";;
		"Discharging") pwr="$pwr%" ;;  *) pwr="?$pwr%" ;;
	esac;
	echo -e "$icon $pwr"; }

volume() {
	vol="$(pactl list sinks | awk '/Volume:/{print $5; exit}' | tr -d '%')"
	if [ "$vol" -ge 40 ]; then echo -e "󰕾 $vol";
	elif [ "$vol" -lt 40 ] && [ "$vol" -ge 20 ]; then echo -e "󰖀 $vol";
	elif [ "$vol" -lt 20 ]; then echo -e "󰕿 $vol";
	fi }

brightness() {
	bgt="$(brightnessctl | grep -oP '\d+(?=%)')"
	echo -e "󰌶 $bgt%"; }

clock() {
    dte="$(date +"%A   󱨰  %d/%b  󰔛  %I:%M %p" | sed 's/  / /g')"
    echo -e "$dte"
}

network(){
	ssid="$(iw dev | awk '/ssid/{print $2}')"; icon=" "
	signal=$(nmcli -t -f SIGNAL device wifi | head -n1 )
	case "$ssid" in
		"") ssid="NULL";;  *) ;;
	esac;
	if [ "$signal" = "--" ] || [ -z "$signal" ]; then icon="󰣽"
    	else
		
		if [ "$signal" -ge 80 ]; then icon="󰣺";
		elif [ "$signal" -ge 60 ] && [ "$signal" -lt 80 ]; then icon="󰣸";
		elif [ "$signal" -ge 40 ] && [ "$signal" -lt 60 ]; then icon="󰣶";
		elif [ "$signal" -ge 20 ] && [ "$signal" -lt 40 ]; then icon="󰣴";
	    	else icon="󰣾";
		fi
	fi
	echo -e "$icon $ssid"; }	

keyboard(){
	kb=$(setxkbmap -query | awk '/layout/ {print $2}')
	case "$kb" in
		"gb") kb="Uk";; 	"us") kb="Us";;
		"latam") kb="Es";;	*) kb=$kb;; 
	esac;
	echo -e "󰓺 :$kb"; }

while true; do	
	xsetroot -name "  [ $(keyboard)  $(battery)  $(network) - $(clock) ]  "		
	sleep 5s
done &
