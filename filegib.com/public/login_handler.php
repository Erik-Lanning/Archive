<?php
	//login_handler.php by Erik Lanning on 4/15/2013
	//Handles logins from the main page
	require "globals.php";
	if(isset($_POST['emaillogin'])) {
		$email = cleanInput($_POST['emaillogin']);
	} else {
		echo 'Email field is empty, please enter an email.<br/>';
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/">';
		exit();	
	}
	if(isset($_POST['passwordlogin'])) {
		$password = cleanInput($_POST['passwordlogin']);
	} else {
		echo 'Password field is empty, please enter a password.<br/>';
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/">';
		exit();		
	}
	
	//call the SQL server and authenticate the user
	$password = md5($md5salt.$password);
	$email = $mysqli->real_escape_string($email);
	$sqlcall = "SELECT email, password, verified_status, contributer_status FROM users WHERE email = '$email'";
	$execquery = $mysqli->query($sqlcall);
	if($execquery) {
		$row = $execquery->fetch_row();
		if($row[1] == $password) { //correct password for the email
			//start session
			$_SESSION['email'] = $row[0];
			$_SESSION['verified_status'] = $row[2];
			$_SESSION['contributer_status'] = $row[3];			
			echo '<meta http-equiv="refresh" content="0; url=http://filegib.com/">';
			exit();
			
		} else {
			echo "Invalid password for this email. Please try again.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/">';
			exit();		
		}
	}
?>