
var XMLHttp;

function init() {
    if(navigator.appName == "Microsoft Internet Explorer") {
	XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
    } else {
	XMLHttp = new XMLHttpRequest();
    }
}

function checkName () {

    var uname = document.getElementById('uname').value;

    if (uname.indexOf('~!&') != -1){
	document.getElementById('response_area').innerHTML = 'Username cannot contain the sequence ~!&';;
    } else{
	document.getElementById('response_area').innerHTML = 'Good username!';;
	}
}