<?php 
//advanced upload handler for contributers by Erik Lanning on 4/18/2013
require "globals.php"; 
if(!isset($_SESSION['contributer_status']) || $_SESSION['contributer_status'] != 1) {
		echo "Advanced file uploading is for contributers only, sorry.<br/>";
		echo "Redirecting in 5 seconds.";
		echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/">';
		exit();	
}
?>
<!doctype html>
<html>
	<meta charset="utf-8">
	<head>
		<title>File Gib - Upload any file</title>
		<link rel="icon" href="/favicon.ico" type="image/ico" />
		<link rel="icon" href="/favicon.png" type="image/png" />
		<!--CSS Stylesheets-->
		<link rel="stylesheet" type="text/css" href="<?php echo $rootdir; ?>/css/bootstrap.css" />
		<link rel="stylesheet" type="text/css" href="<?php echo $rootdir; ?>/css/main.css" />
		<link rel="stylesheet" type="text/css" href="<?php echo $rootdir; ?>/plugins/uploader/uploadify.css" />
		<!--JavaScript Plugins-->
		<script type="text/javascript" src="http://code.jquery.com/jquery-1.7.2.min.js"></script>
		<script type="text/javascript">
		function passwordon() {
			document.getElementById("passwordinput").style.display = "inline";
		}
		function passwordoff() {
				document.getElementById("passwordinput").style.display = "none";	
		}
		function submitlogin()
		{
		  document.loginform.submit();
		}
		function validate() {
			if(document.advuploadform.title.value == "") {
				 alert( "Please provide a title for the file" );
				 document.advuploadform.title.focus() ;
				 return false;			
			}
			if(document.advuploadform.description.value == "") {
				 alert( "Please provide a description for the file" );
				 document.advuploadform.description.focus();
				 return false;				
			}
			return( true );
		
		}
		</script>

		<style type="text/css">
		#advupload {
			border-radius: 5px;
			border-style:solid; 
			border-width: thin; 
			width: 500px; 
			height: 500px;
			margin-left:35%;
			margin-right:45%;
			padding-left: 20px;
			padding-top: 20px;
		}
		label {
			font-weight:bold;
		}
		</style>
		<meta name="google-translate-customization" content="fe8b5d785c734dcb-749c68abc96a8982-g9f8c88bba15eea0b-b"></meta>
	</head>
	<body>
		<div id="navigation-bar">
			<div id="navwrapper">
				<ul class="floatleft" id="nav">
						<li><a href="<?php echo $rootdir; ?>/index.php">Home</a></li>
						<?php
							if(isset($_SESSION['email']) && isset($_SESSION['contributer_status']) && isset($_SESSION['verified_status'])) { //user is logged in
								echo "<li><a href=\"/editacc.php\">".$_SESSION['email']."</a></li>";
								if ($_SESSION['contributer_status'] == 0) { //not a contributer account so different nav
									echo "<li><a href=\"/contributerup.php\">Upgrade to Contributer</a></li> ";
								}
								elseif($_SESSION['contributer_status'] == 1) { //has contributer status
									echo "<li><a href=\"/filehandlerpage.php\">Your Files</a></li>";
									echo "<li><a href=\"/advancedupload.php\">Advanced Upload</a></li>";
								}
							}
							else {
								echo '
								<li><a href="#">Login <span class="arrowdown">&#9660;</span></a>
									<ul>
										<ul>
											<form name="loginform" method="post" action="login_handler.php"> 
												<li>Email: <input type="text" name="emaillogin" class="input-medium" /></li>
												<li>Password: <input type="password" name="passwordlogin" class="input-medium" /> </a></li>
												<li><a href="#" onclick="submitlogin()">Submit</a></li>
												<li><a href="/register.php">Register</a></li>
											</form>
										</ul>
									</ul>
								</li>
								<li><a href="/contributers.php">Become A Contributer</a></li>';
							}
						?>
				</ul>
				<ul class="floatright" id="nav">
							<?php
							if(isset($_SESSION['email']) && isset($_SESSION['contributer_status']) && isset($_SESSION['verified_status'])) { //user is logged in
								echo "<li style=\"padding-right:250px;\"><a href=\"/logout_handler.php\">Logout</a><li>";
							}
							?>
				</ul>
				<br class="clear" />
			</div>
		</div>
		<form id="searchbar" method="post" action="search.php">
			<div class='input-append'>
				<input placeholder="Search..." id="searchinputbox" name="searchinputbox"/>
					<button class='btn add-on' type="submit">
						<i class="icon-search"></i>
					</button>
			</div>
		</form>	
			<div id="contentbox" style="margin-top:80px;">
			<center>
				<div><font size="5">Advanced Upload</font></div>
			</center>
				<div id="advupload">
				<form name="advuploadform" method="post" action="advancedupload_handler.php" enctype="multipart/form-data" onsubmit="return(validate());" >
					<label for="title">
						Title
					</label>
					<input id="title" name="title" type="text" />
					<label for="description">
						Description
					</label>
					<textarea id="description" name="description" rows="4" cols="60" style="width:450px;"></textarea>
					<label for="keywords">
						Search Keywords<br/>
						<font size="1" color="grey">separated by commas "example1, example2, etc"</font>
					</label>
					<input id="searchkeywords" name="searchkeywords" type="text" />
					<label for="passwordprotect">
						Password Protect
					</label>
					<input type="radio" name="passwordprotect" value="on" onclick="passwordon()">Yes</input>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" name="passwordprotect" value="off" onclick="passwordoff()" checked="checked">No</input>
					<div id="passwordinput" style="display: none;">
					<label for="password">
						Password
					</label>
					<input id="file_password" name="file_password" type="text" />
					</div>
					<label for="fileselect">
						<br/>File Select
					</label>
					<input type="file" name="upload_place" id="upload_place" /><br/>
					<center>
						<input type="submit" value="Upload">
					</center>
				</form>
				</div>
			</div>
		<div id="footer">
				<div id="bottomlist">
				<div id="google_translate_element" style="position: absolute; bottom: 0; left: 0; "></div><script type="text/javascript">
				function googleTranslateElementInit() {
				  new google.translate.TranslateElement({pageLanguage: 'en', layout: google.translate.TranslateElement.InlineLayout.HORIZONTAL}, 'google_translate_element');
				}
				</script><script type="text/javascript" src="//translate.google.com/translate_a/element.js?cb=googleTranslateElementInit"></script>
					 <a href="<?php echo $rootdir; ?>/policy.php">Privacy Policy</a>
					 <a href="<?php echo $rootdir; ?>/tos.php">Terms of Use</a>
					 <a href="<?php echo $rootdir; ?>/contact.php">Contact</a>
				</div>
		</div>
	</body>
</html>