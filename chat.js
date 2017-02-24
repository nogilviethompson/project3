
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

function sendMessage(){
	var uname = document.getElementById('uname').value;
	var message = document.getElementById('message').value;
	
    XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=SEND"
						 + "&username=" + uname
						 + "&message=" + message
						 ,true);
	
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						+ "&command=GET"
						,true);
}

function getResponse(){
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=GET"
						 ,true);
	
	XMLHttp.onreadystatechange=function() {
	document.getElementById('response_area').innerHTML = XMLHttp.responseText;;
    }
}

function autoRefresh(){
    intVar = setInterval(function(){ getResponse()}, 1000);
}

function hangUp(){
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=KILL"
						 ,true);
}

