<?php
/*
Uploadify
Copyright (c) 2012 Reactive Apps, Ronnie Garcia
Released under the MIT License <http://www.opensource.org/licenses/mit-license.php> 

Modified by Erik Lanning on 2/6/2013
*/
	//Global imports go here:
	require_once("globals.php");
//$verifyToken = md5('unique_salt' . $_POST['timestamp']);
//
if (!empty($_FILES)) {
	if(!isset($_SESSION['email'])) {
		echo "You weren't logged in when you uploaded this file. Please login then try uploading.<br/>";
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/advancedupload.php">';
		exit();	
	}
	if(!isset($_SESSION['contributer_status']) || $_SESSION['contributer_status'] != 1) {
		echo "Advanced file uploading is for contributers only, sorry.<br/>";
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/">';
		exit();		
	}
	if(isset($_POST['title'])) {
		if(strlen($_POST['title']) > 30) {
			echo "Maximum length for Titles is 30 or less characters, please shorten the title.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/advancedupload.php">';
			exit();
		}
		$file_title = cleanInput($_POST['title']);
	} else {
			echo "Please include a title for your file.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/advancedupload.php">';
			exit();	
	}
	if(isset($_POST['description'])) {
		if(strlen($_POST['description']) > 300) {
			echo "Maximum length for Descriptions is 300 or less characters, please shorten the description.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/advancedupload.php">';
			exit();
		}
		$file_description = $_POST['description'];
	} else {
			echo "Please include a description for your file.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/advancedupload.php">';
			exit();	
	}
	if(isset($_POST['searchkeywords'])) {
		if(strlen($_POST['description']) > 50) {
			echo "Maximum length for Search Keywords is 50 or less characters, please use less keywords.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/advancedupload.php">';
			exit();
		}
		$searchkeywords = cleanInput($_POST['searchkeywords']);
	} else {
			echo "Please include search words for your file.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/advancedupload.php">';
			exit();	
	}
	if(isset($_POST['passwordprotect']) && $_POST['passwordprotect'] == "on") {
		if(!isset($_POST['file_password'])) {
			echo "You checked 'Password Protect' but forgot to include a password. Please include a password.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/advancedupload.php">';
			exit();			
		}
		if(strlen($_POST['file_password']) > 35) {
			echo "Maximum length for File Passwords is 35 or less characters, please use less characters.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/advancedupload.php">';
			exit();
		}
		$file_password = cleanInput($_POST['file_password']);
	}
	$tempFile = $_FILES['upload_place']['tmp_name'];
	$fileParts = pathinfo($_FILES['upload_place']['name']);
	//MySQL serialization data
	$file_id = make_id(6, $allowedchars); //trimmed to first 6 digits
	$file_id = "adv" . $file_id;
	//Make sure file_id isn't a duplicate
		$quickquery = "SELECT * FROM advfileindex WHERE key_id='$file_id'";
		$executequery = $mysqli->query($quickquery);
		$num_rows = $executequery->num_rows;

		while ($num_rows > 0) { //duplicate detected so keep making IDs
			$file_id = make_id(6, $allowedchars);
			$file_id = "adv" . $file_id;
			$executequery = $mysqli->query($quickquery);
			$num_rows = $executequery->num_rows;	  
		}
	mkdir("advfiles/".$file_id);
	$targetPath = $_SERVER['DOCUMENT_ROOT'] . $advancedFolder ."/". $file_id;
	$file_hash = md5_file($tempFile);
	$file_name = $fileParts['basename'];
	$file_creation_time = date("m.d.y");
	$file_type = $fileParts['extension'];
	$file_size = display_filesize(filesize($tempFile));
	$file_views = 1;
	$file_download = "http://filegib.com".$advancedFolder."/". $file_id ."/". $_FILES['upload_place']['name'];
	$targetFile = rtrim($targetPath,'/') . '/' . $_FILES['upload_place']['name'];

	//If large file check if hash already uploaded

	//MySQL server calls - create the database entry
	$email = $_SESSION['email'];
	$new_file = "INSERT INTO advfileindex (users_email, url_id, file_name, file_hash, file_type, file_views, file_path, file_size, creation_time, file_title, file_description, file_keywords, file_password)
	VALUES
	('$email', '$file_id', '$file_name', '$file_hash', '$file_type', '$file_views', '$file_download', '$file_size', '$file_creation_time', '$file_title', '$file_description', '$searchkeywords', '$file_password')";
	$mysqli->query($new_file);
	$mysqli->close();
	//Finally move the file
	move_uploaded_file($tempFile,$targetFile);
	//Redirect the user to the new uploaded file:
	echo "<meta http-equiv=\"refresh\" content=\"0; url=http://filegib.com/".$file_id."\">";

}  else {
	//no files uploaded error
	print "Error: file not uploaded. Please give us a moment and try again later.";
}
?>