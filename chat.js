<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======

>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======

>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	var com = 'USER';
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=" + com
						 + "&username=" + uname
						 ,true);
						 
	XMLHttp.onreadystatechange=function() {
	document.getElementById('username_show').innerHTML = XMLHttp.responseText;
    }
	
	document.getElementById('uname').disabled = true;
	document.getElementById('message').disabled = false;
	document.getElementById('unameButton').style.visibility = "hidden";
	autoRefresh();
=======
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba

	document.getElementById('uname').disabled = true;
	document.getElementById('username_show').innerHTML = 'Your username is '+uname;
	document.getElementById('message').disabled = false;
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
}

function sendMessage(){
	var uname = document.getElementById('uname').value;
	var message = document.getElementById('message').value;
	var com = 'SEND';
	
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
=======
    XMLHttp.open("GET", "/cgi-bin/grigullb_chatAjax.cgi?"
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
    XMLHttp.open("GET", "/cgi-bin/grigullb_chatAjax.cgi?"
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
    XMLHttp.open("GET", "/cgi-bin/grigullb_chatAjax.cgi?"
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
						 + "&command=" + com
						 + "&username=" + uname
						 + "&message=" + message
						 ,true);
						 
	XMLHttp.send(null);
}

function getResponse(){
	var com = 'GET';
	
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
=======
	XMLHttp.open("GET", "/cgi-bin/grigullb_chatAjax.cgi?"
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
	XMLHttp.open("GET", "/cgi-bin/grigullb_chatAjax.cgi?"
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
	XMLHttp.open("GET", "/cgi-bin/grigullb_chatAjax.cgi?"
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
						 + "&command=" + com
						 ,true);
	
	XMLHttp.onreadystatechange=function() {
	document.getElementById('response_area').innerHTML = XMLHttp.responseText;;
    }
	XMLHttp.send(null);
}

var intVar

function autoRefresh(){
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    var intVar = setInterval(function(){ getResponse()}, 2000);
}

function hangUp(){
	var com = 'KILL';
	XMLHttp.open("GET", "/cgi-bin/ogilviethompsonh_chatAjax.cgi?"
						 + "&command=" + com
						 ,true);
}
=======
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
    var intVar = setInterval(function(){ getResponse()}, 10000);
}

function hangUp(){
	clearInterval(intVar);
	var com = 'KILL';
	XMLHttp.open("GET", "/cgi-bin/grigullb_chatAjax.cgi?"
						 + "&command=" + com
						 ,true);
}

<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
=======
>>>>>>> d61db7679a6a66beda9f0c467b363de8754e35ba
