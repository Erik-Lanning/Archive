<?php
	require "globals.php"
	
	//make sure the user is logged in
	if(!isset($_SESSION['email'])) {
			exit();	
	}
	if(!isset($_SESSION['contributer_status'])) {
			exit();			
	}
	if(isset($_POST['fileid'])) {
		$file_id = $_POST['fileid'];
		$email = $_SESSION['email'];
		//delete the file from MySQL
		$email = $mysqli->real_escape_string($email);
		$file_id = $mysqli->real_escape_string($file_id);
		$sqlcall = "SELECT file_path FROM advfileindex WHERE url_id='$file_id' AND users_email='$email' ";
		if($executequery = $mysqli->query($sqlcall)) {
			$all_rows = $executequery->fetch_row();
			$filepath = $all_rows[0]; //files path from SQL call
		}
		$sqlcall = "DELETE FROM advfileindex WHERE url_id='$file_id' AND users_email='$email' ";
		if($executequery = $mysqli->query($sqlcall)) {
			echo "Successfully deleted file.";
		}
		//detele file from storage
		if(isset($filepath)) {
			unlink($filepath);
		}
	} else {
		exit('Error Deleting file.');
	}
	
?>