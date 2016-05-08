<?php
	// register_handler.php by Erik Lanning
	// 4/13/2013
	// Description: Handles the submitted form inputs
	
	//for the MySQL connection and the md5 salt
	require "globals.php";
	
	function check_email($var) {
		if(strlen($var) > 40) {
			echo "Please enter an email 40 characters or less in length.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/register.php">';
			exit();
		}
		if(!filter_var($var, FILTER_VALIDATE_EMAIL)) {
			echo "Please enter a valid email, so we can email you a verification link.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/register.php">';
			exit();
		}
		else {
			return $var;
		}
		return $var;
	}
	function check_password($var) {
		if(strlen($var) < 6) {
			echo "Please enter a password that is more than 6 digits long.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/register.php">';
			exit();
		}
		if(strlen($var) > 32) {
			echo "Please enter a password under 32 digits.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/register.php">';	
			exit();
		} else {
			return $var;
		}
		return $var;
	}
	if(isset($_POST['email'])) {
		$email = cleanInput($_POST['email']);
	} else {
		echo "Please enter an email address.<br/>";
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/register.php">';
		exit();
	}
	if(isset($_POST['password'])) {
		$password = cleanInput($_POST['password']);
	} else {
		echo "Please enter a 6+ digit password.<br/>";
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/register.php">';
		exit();
	}
	if(isset($_POST['termsofservice']) && $_POST['termsofservice'] != 'agree') {
		echo "You must agree to our Terms of Service to register an account.<br/>";
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/register.php">';
		exit();
	}
	//TODO captcha 
	
	//Sanitize and check inputs
	$email = check_email($email);
	$password = check_password($password);
	//encrypt the password
	$password = md5($md5salt.$password);

	//Check if duplicate email
	$quickquery = "SELECT * FROM users WHERE email='$email'";
	$executequery = $mysqli->query($quickquery);
	$num_rows = $executequery->num_rows;
	
	if ($num_rows > 0) { //duplicate detected
		echo "This email is already registered, sorry.<br/>";
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/register.php">';
		exit();
	}
	//Insert user into SQL and send verification email
	$email = $mysqli->real_escape_string($email);
	$password =  $mysqli->real_escape_string($password);
	$sqlcall = "INSERT INTO users (email, password, verified_status, contributer_status)
				VALUES ('$email', '$password', 0, 0)";
	$executequery = $mysqli->query($sqlcall);
	if(!$executequery) {
		echo "Problem connecting to the server, please try registering again later.<br/>";
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/">';
		exit();		
	}
	//Initialize this new users session
	$_SESSION['email'] = $email;
	$_SESSION['verified_status'] = 0;
	$_SESSION['contributer_status'] = 0;
	echo 'A verification email has been sent. Please check it to verify your account.<br/>';
	echo "Redirecting in 5 seconds.";
	echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/">';
	exit();
?>