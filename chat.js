var XMLHttp;
var intVar;
var sendBusy = false;
var chosenChat;

function init() {
    if(navigator.appName == "Microsoft Internet Explorer") {
	XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
    } else {
	XMLHttp = new XMLHttpRequest();
    }
	
	document.getElementById('chatForm').style.visibility = "hidden";
	document.getElementById('messageForm').style.visibility = "hidden";
}

function user(){
	var com = 'CHECK';
	var uname = document.getElementById('uname').value;
	XMLHttp.open("GET", "/cgi-bin/xuy_chatAjax.cgi?"
						 + "&command=" + com
						 + "&username=" + uname
						 ,true);
						 
	XMLHttp.onreadystatechange=function(){
		if(XMLHttp.readyState == 4){
			var response = XMLHttp.responseText
			if (response === "Sorry, but that username has already been taken"){
				document.getElementById('userMatch').innerHTML = response;
				document.getElementById('message').disabled = true;
				clearInterval(intVar);
				document.getElementById('hangUpButton').disabled = true;
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
	
	if (message === ""){
		return;
	}
	
	sendBusy = true;
	
	XMLHttp.open("GET", "/cgi-bin/xuy_chatAjax.cgi?"
						 + "&command=" + com
						 + "&username=" + uname
						 + "&message=" + message
						 ,true);
	XMLHttp.send(null);
	document.messageForm.textInput.value = "";
}

function getResponse(){
	var com = 'GETCHATS';
	XMLHttp.open("GET", "/cgi-bin/xuy_chatAjax.cgi?"
						 + "&command=" + com
						 ,true);
	
	XMLHttp.onreadystatechange=function() {
		if(XMLHttp.readyState == 4){
			var responseMessage = XMLHttp.responseText;
			var messageArray = responseMessage.split('~chatname~');
			console.log(messageArray.length);
			$('#chatLog_area').empty();
			for(var i = 0;i<messageArray.length; i++){
				$('#chatLog_area').append("<div class=chatListItem>"+messageArray[i]+"</div>");
			}
			sendBusy = false;
		    console.log("Get Message response:"+XMLHttp.responseText);
		}
	}
	XMLHttp.send(null);
}

function getMessages(){
	var com = 'GETMESSAGES';
	
	XMLHttp.open("GET", "/cgi-bin/xuy_chatAjax.cgi?"
						 + "&command=" + com
						 + "&chatName=" + chosenChat
						 ,true);
	
	XMLHttp.onreadystatechange=function() {
		if(XMLHttp.readyState == 4){
			var response = XMLHttp.responseText;
			document.getElementById('response_area').innerHTML = response;
			sendBusy = false;
			}
		}
	XMLHttp.send(null);
	}

function refreshChats(){
    intVar = setInterval(function(){ getResponse()}, 2000);
}

function removeUser(){
	clearInterval(intVar);
	document.getElementById('username_show').innerHTML = "";
	document.getElementById('connect').innerHTML = "";
	document.getElementById('unameButton').style.visibility = "visible";
	document.getElementById('uname').disabled = false;
	document.getElementById('message').disabled = true;
	document.getElementById('hangUpButton').disabled = true;
	document.getElementById('newChatButton').disabled = true;
	document.getElementById('chatForm').style.visibility = "hidden";
	document.getElementById('messageForm').style.visibility = "hidden";
	var com = 'REMOVE';

	sendBusy = true;
	
	XMLHttp.open("GET", "/cgi-bin/xuy_chatAjax.cgi?"

						 + "&command=" + com
						 ,true);
	document.usernameForm.unameInput.value = "";
	XMLHttp.send(null);
}

function checkName() {
    var uname = document.getElementById('uname').value;
	document.getElementById('uname').disabled = true;
	document.getElementById('message').disabled = false;
	document.getElementById('hangUpButton').disabled = false;
	document.getElementById('newChatButton').disabled = false;
	document.getElementById('unameButton').style.visibility = "hidden";
	document.getElementById('chatLog_area').style.visibility = "visible";
	document.getElementById('username_show').innerHTML = "Your username is "+uname;
	refreshChats();
	user();
}

function newChat(){
	document.getElementById('newChatButton').disabled = true;
	document.getElementById('chatForm').style.visibility = "visible";
	//document.getElementById('chatLog_area').style.visibility = "hidden";
	document.getElementById('uname').disabled = true;
}

function createChat(){
	document.getElementById('uname').disabled = true;
	document.getElementById('messageForm').style.visibility = "visible";
	document.getElementById('message').disabled=false;
	var uname = document.getElementById('uname').value;
	var chatName=document.getElementById('chatName').value;
	document.getElementById('response_area').innerHTML = "Your chatroom's name is "+chatName;
	var com = 'NEWCHAT';
	XMLHttp.open("GET", "/cgi-bin/xuy_chatAjax.cgi?"
						 + "&command=" + com
						 + "&username=" + uname
						 +"&chatName"+chatName
						 ,true);
	document.usernameForm.unameInput.value = "";
	XMLHttp.send(null);
	
	
}

$(document).ready(function() {
    
	$('.username').keydown(function(event) {
        if (event.keyCode == 13) {
            checkName();
            return false;
         }
    });
	
    $('.messagearea').keydown(function(event) {
        if (event.keyCode == 13) {
            sendMessage();
            return false;
         }
    });
    
	$(document).on("click", ".chatListItem",function(event){

		var com = 'JOINCHAT';
		var uname = document.getElementById('uname').value;
		var chatName = $(this).html();
		chosenChat = chatName;
	
		document.getElementById('newChatButton').disabled = true;
		document.getElementById('messageForm').style.visibility = "visible";
		document.getElementById('chatLog_area').style.visibility = "hidden";
	
		console.log(chatName);
	
		clearInterval(intVar);
		
		XMLHttp.open("GET", "/cgi-bin/xuy_chatAjax.cgi?"

						 + "&command=" + com
						 + "&username=" + uname
						 + "&chatName=" + chatName
						 ,true);
	
		XMLHttp.onreadystatechange=function() {
			if(XMLHttp.readyState == 4){
				var response = XMLHttp.responseText
				document.getElementById('connect').innerHTML = response;
				if (response === "Sorry, but the chatroom is full"){
					document.getElementById('message').disabled = true;
					clearInterval(intVar);
					document.getElementById('hangUpButton').disabled = true;
				}
			}
		}
		refreshChats();
    });
});