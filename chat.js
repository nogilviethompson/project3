var XMLHttp;

function init() {
    if(navigator.appName == "Microsoft Internet Explorer") {
	XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
    } else {
	XMLHttp = new XMLHttpRequest();
    }
}

function user(){
	var com = 'USER';
	var uname = document.getElementById('uname').value;
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=" + com
						 + "&username=" + uname
						 ,true);
						 
	XMLHttp.onreadystatechange=function() {
	document.getElementById('connect').innerHTML = XMLHttp.responseText;
	}
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
		console.log(XMLHttp.readyState);
		if(XMLHttp.readyState == 4){
			document.getElementById('response_area').innerHTML = XMLHttp.responseText;
		}
	}
	XMLHttp.send(null);
}

var intVar

function autoRefresh(){
    var intVar = setInterval(function(){ getResponse()}, 2000);
}

function hangUp(){
	clearInterval(intVar);
	var com = 'KILL';
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=" + com
						 ,true);
}

function checkName() {
    var uname = document.getElementById('uname').value;
	
	document.getElementById('uname').disabled = true;
	document.getElementById('message').disabled = false;
	document.getElementById('unameButton').style.visibility = "hidden";
	document.getElementById('username_show').innerHTML = "Your username is "+uname;
	user();
	autoRefresh();
}