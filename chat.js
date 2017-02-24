
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

	document.getElementById('uname').disabled = true;
	document.getElementById('username_show').innerHTML = 'Your username is '+uname;
	document.getElementById('message').disabled = false;
}

function sendMessage(){
	var uname = document.getElementById('uname').value;
	var message = document.getElementById('message').value;
	var com = 'SEND';
	
    XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=" + com
						 + "&username=" + uname
						 + "&message=" + message
						 ,true);
						 
	XMLHttp.send(null);
}

function getResponse(){
	var com = 'GET';
	
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=" + com
						 ,true);
	
	XMLHttp.onreadystatechange=function() {
	document.getElementById('response_area').innerHTML = XMLHttp.responseText;;
    }
	XMLHttp.send(null);
}

function autoRefresh(){
    intVar = setInterval(function(){ getResponse()}, 1000);
}

function hangUp(){
	var com = 'KILL';
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=" + com
						 ,true);
}

