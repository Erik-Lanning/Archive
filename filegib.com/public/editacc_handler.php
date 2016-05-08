<?php
	//editacc_handler.php by Erik Lanning [4/30/2013]
	//Description: Manages user changes to their accounts password, redirects to home when done
	//NOTE: no need to check confirm new password, that was client side only as a double check
	require "globals.php";
	if(!isset($_SESSION['email'])) {
			echo '<meta http-equiv="refresh" content="0; url=http://filegib.com/">';
			exit();	
	} else {
		$users_email = $_SESSION['email'];
	}
	if(!isset($_POST['currentpassword'])) {
		echo 'You forgot to set your current password.<br/>';
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/editacc.php">';
		exit();	
	} else {
		$currentpassword = cleanInput($_POST['currentpassword']);
	}
	if(!isset($_POST['newpassword'])) {
		echo 'You forgot to enter a new password.<br/>';
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/editacc.php">';
		exit();	
	} else {
		$newpassword = cleanInput($_POST['newpassword']);
	}
	//Update the users password
	//Insert user into SQL and send verification email
	$users_email = $mysqli->real_escape_string($users_email);
	$currentpassword = $mysqli->real_escape_string($currentpassword);
	$newpassword = $mysqli->real_escape_string($newpassword);
	$sqlcall = "UPDATE users SET password='$newpassword' WHERE email='$users_email' AND password='$currentpassword'";
	$executequery = $mysqli->query($sqlcall);
	if(!$executequery) {
		echo "Problem connecting to the server, please try registering again later.<br/>";
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/">';
		exit();		
	} else {
		echo 'Password successfully updated.<br/>';
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/">';
		exit();		
	}
?>