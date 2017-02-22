
var XMLHttp;

function init() {
    if(navigator.appName == "Microsoft Internet Explorer") {
	XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
    } else {
	XMLHttp = new XMLHttpRequest();
    }
}

<<<<<<< HEAD
function checkName() {
    var uname = document.getElementById('uname').value;

    if (uname.indexOf('~!&') != -1){
	document.getElementById('username_show').innerHTML = 'Username cannot contain the sequence ~!&';
    } else{
	document.getElementById('username_show').innerHTML = 'Your username is '+uname;
	document.getElementById('uname').disabled = true;
	document.getElementById('message').disabled = false;
=======
function checkName () {

    var uname = document.getElementById('uname').value;

    if (uname.indexOf('~!&') != -1){
	document.getElementById('response_area').innerHTML = 'Username cannot contain the sequence ~!&';;
    } else{
	document.getElementById('response_area').innerHTML = 'Good username!';;
>>>>>>> 524843d833cf43c1251f66dc14b18852063556de
	}
}