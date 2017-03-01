var XMLHttp;
var intVar;
var sendBusy = false;

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
	XMLHttp.onreadystatechange=function(){
		if(XMLHttp.readyState == 4){
			var response = XMLHttp.responseText
			document.getElementById('connect').innerHTML = response;
			if (response === "Sorry, but the chatroom is full"){
				document.getElementById('message').disabled = true;
				clearInterval(intVar);
			}
		}
	}
	XMLHttp.send(null);
}

function sendMessage(){
	var uname = document.getElementById('uname').value;
	var message = document.getElementById('message').value;
	var com = 'SEND';
	if (sendBusy){
		return;
	}
	
	sendBusy = true;
	
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=" + com
						 + "&username=" + uname
						 + "&message=" + message
						 ,true);
	XMLHttp.send(null);
	document.chatForm.textInput.value = "";
}

function getResponse(){
	var com = 'GET';
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=" + com
						 ,true);
	
	XMLHttp.onreadystatechange=function() {
		if(XMLHttp.readyState == 4){
			document.getElementById('response_area').innerHTML = XMLHttp.responseText;
			sendBusy = false;
		}
	}
	XMLHttp.send(null);
}

function autoRefresh(){
    intVar = setInterval(function(){ getResponse()}, 2000);
}

function removeUser(){
	clearInterval(intVar);
	document.getElementById('username_show').innerHTML = "";
	document.getElementById('connect').innerHTML = "";
	document.getElementById('unameButton').style.visibility = "visible";
	document.getElementById('uname').disabled = false;
	document.getElementById('message').disabled = true;
	var com = 'REMOVE';
	var uname = document.getElementById('uname').value;
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=" + com
						 + "&username=" + uname
						 ,true);
	document.usernameForm.unameInput.value = "";
	XMLHttp.send(null);
}

function checkName() {
    var uname = document.getElementById('uname').value;
	document.getElementById('uname').disabled = true;
	document.getElementById('message').disabled = false;
	document.getElementById('unameButton').style.visibility = "hidden";
	document.getElementById('username_show').innerHTML = "Your username is "+uname;
	autoRefresh();
	user();
}