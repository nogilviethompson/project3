
var XMLHttp;

function init() {
    if(navigator.appName == "Microsoft Internet Explorer") {
	XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
    } else {
	XMLHttp = new XMLHttpRequest();
    }
}

function checkName() {
    var uname = document.getElementById('uname').value;

	document.getElementById('username_show').innerHTML = 'Your username is '+uname;
	document.getElementById('uname').disabled = true;
	document.getElementById('message').disabled = false;
}

function getResponse(){
	var uname = document.getElementById('uname').value;
	var message = 
}

function hangUp(){
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatCGI.cgi?"
						 + "&killmessage=**KILLKILLKILL**"
						 ,true);
}