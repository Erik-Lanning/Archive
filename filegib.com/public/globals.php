<?php
	//Global Functions, by Erik Lanning on 2/10/2013
	//Description: Holds all the functions and flexible data to allow easy scaling changes
	
	//cookies
	if(!isset($_SESSION['email'])) {
		session_start();
	}
	//Database connect info
	$server_name = "localhost";
	$username = "filegibuser2";
	$sqlpass = "08127b4sb4ll12";
	$dbname = "filegibdb";
	$mysqli = new mysqli($server_name, $username, $sqlpass, $dbname);
	$rootdir = "";
	$baseurl = "";
	if(!$mysqli) {
		die("Error connecting to the database, try again later.");
	}	
	//global variables
	$supported_fimages = array("aac", "ai", "aiff", "avi", "dat", "dmg", "exe", "flv", "ics", "java", "key", "mid", "mpg", "py", "qt", "rar", "rb", "rtf", "sql", "wav", "xml", "yml", "zip");
	$supported_adv_fimages = array("aac", "ai", "aiff", "avi", "bmp", "c", "cpp", "css", "dat", "dmg", "doc", "dotx", "dwg", "dxf", "eps", "exe", "flv", "gif", "h", "hpp", "html", "ics", "iso", "java", "jpg", "key", "mid", "mp3", "mp4", "mpg", "odf", "ods", "odt", "otp", "ots", "ott", "pdf", "php", "png", "ppt", "psd", "py", "qt", "rar", "rb", "rtf", "sql", "tga", "tgz", "tiff", "txt", "wav", "xls", "xlsx", "xml", "yml", "zip");
	$images = array("bmp", "tiff", "png", "jpg", "gif");
	$gdocfiles = array("mpeg4", "3gpp", "mov", "avi", "mpegps", "wmv", "txt", "css", "html", "c", "cpp", "h", "hpp", "js", "doc", "docx", "xls", "xlsx", "ppt", "pptx", "pdf", "pages", "ai", "psd", "dxf", "svg", "eps", "ps", "ttf", "xps");
	$highrisk_files = array("exe", "rar", "zip", "msi");	
	$music_files = array("mp3");
	$video_files = array("ogg", "mp4", "webm");
	//Random Letter/number generator
	$allowedchars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		// Define a destination
	$targetFolder = '/up'; // Relative to the root
	$advancedFolder = '/advfiles';
	$md5salt = "x15Lsdfo25PdNwMsdf3324SSSDWER4WcjjjFWEF542";
	//functions
	function make_id($N, $alphabet)
	{
	  $s = "";
	  for ($i = 0; $i != $N; ++$i)
		$s .= $alphabet[mt_rand(0, strlen($alphabet) - 1)];
	  return $s;
	}
	function display_filesize($filesize) {
		if(is_numeric($filesize)){
		$decr = 1024; $step = 0;
		$prefix = array('Bytes','KB','MB','GB','TB','PB');
		   
		while(($filesize / $decr) > 0.9){
			$filesize = $filesize / $decr;
			$step++;
		}
		return round($filesize,2).' '.$prefix[$step];
		} else {
			return 'NaN';
		}	   
	}
	function cleanInput($input) {
	 
	  $search = array(
		'@<script[^>]*?>.*?</script>@si',   // Strip out javascript
		'@<[\/\!]*?[^<>]*?>@si',            // Strip out HTML tags
		'@<style[^>]*?>.*?</style>@siU',    // Strip style tags properly
		'@<![\s\S]*?--[ \t\n\r]*>@'         // Strip multi-line comments
	  );
	 
		$output = preg_replace($search, '', $input);
		$output = stripslashes($output);
		$output = htmlspecialchars($output);
		return $output;
	 }	
?>