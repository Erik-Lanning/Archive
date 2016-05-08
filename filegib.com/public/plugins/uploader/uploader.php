<?php
/*
Uploadify
Copyright (c) 2012 Reactive Apps, Ronnie Garcia
Released under the MIT License <http://www.opensource.org/licenses/mit-license.php> 

Modified by Erik Lanning on 2/6/2013
*/
	//Global imports go here:
	require_once("../../globals.php");
//$verifyToken = md5('unique_salt' . $_POST['timestamp']);
//
if (!empty($_FILES)) {
	$tempFile = $_FILES['Filedata']['tmp_name'];
	$fileParts = pathinfo($_FILES['Filedata']['name']);
	
	//MySQL serialization data
	$file_id = make_id(6, $allowedchars); //trimmed to first 6 digits
	//Make sure file_id isn't a duplicate
		$quickquery = "SELECT * FROM fileindex WHERE key_id='$file_id'";
		$executequery = $mysqli->query($quickquery);
		$num_rows = $executequery->num_rows;

		while ($num_rows > 0) { //duplicate detected so keep making IDs
			$file_id = make_id(6, $allowedchars); 
			$executequery = $mysqli->query($quickquery);
			$num_rows = $executequery->num_rows;	  
		}
	mkdir("../../up/".$file_id);
	$targetPath = $_SERVER['DOCUMENT_ROOT'] . $targetFolder ."/". $file_id;
	$file_hash = md5_file($tempFile);
	$file_name = $fileParts['basename'];
	$file_creation_time = date("m.d.y");
	$file_type = $fileParts['extension'];
	$file_size = display_filesize(filesize($tempFile));
	$file_views = 1;
	$file_download = "http://filegib.com".$targetFolder."/". $file_id ."/".  $_FILES['Filedata']['name'];
	$targetFile = rtrim($targetPath,'/') . '/' . $_FILES['Filedata']['name'];

	//If large file check if hash already uploaded

	//MySQL server calls - create the database entry
	$new_file = "INSERT INTO fileindex (url_id, file_name, file_hash, file_type, file_views, file_path, file_size, creation_time)
	VALUES
	('$file_id', '$file_name', '$file_hash', '$file_type', '$file_views', '$file_download', '$file_size', '$file_creation_time')";
	$mysqli->query($new_file);
	$mysqli->close();
	//Finally move the file
	move_uploaded_file($tempFile,$targetFile);
	//Redirect the user to the new uploaded file:
	echo "http://filegib.com/".$file_id."";

} else {
	//no files uploaded error
	print "Error: file not uploaded. Please give us a moment and try again later.";
}
?>