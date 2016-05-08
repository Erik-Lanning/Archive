<?php
	//logout_handler.php by Erik Lanning [4/25/2013]
	//simply logs the user out and deletes the session
	require "globals.php";
	if(isset($_SESSION['email'])) {
		unset($_SESSION['email']);
	}
	if(isset($_SESSION['verified_status'])) {
		unset($_SESSION['verified_status']);
	}
	if(isset($_SESSION['contributer_status'])) {
		unset($_SESSION['contributer_status']);
	}
	session_destroy(); // this may be redundant with unsets, will optimise later
	echo '<meta http-equiv="refresh" content="0; url=http://filegib.com/">';	
?>