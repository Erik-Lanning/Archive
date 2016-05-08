<?php require "globals.php";
	if(!isset($_SESSION['email'])) {
			echo '<meta http-equiv="refresh" content="0; url=http://filegib.com">';	
			die();
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
		<!--JavaScript Plugins-->
		<script type="text/javascript" src="http://code.jquery.com/jquery-1.7.2.min.js"></script>
		<script language="JavaScript" type="text/javascript">
		function validate() {
			if(document.newpassform.currentpassword.value == "") {
				 alert( "Please provide your current password." );
				 document.newpassform.currentpassword.focus() ;
				 return false;			
			}
			if(document.newpassform.newpassword.value == "") {
				 alert( "Please provide a new password." );
				 document.newpassform.newpassword.focus() ;
				 return false;				
			}
			if(document.newpassform.confirmpassword.value == "") {
				alert( "Please confirm your new password by retyping it." );
				document.newpassform.confirmpassword.focus() ;
				return false;
			}
			if(document.newpassform.confirmpassword.value != document.newpassform.newpassword.value) {
				alert( "Your new password and confirmation password don't match.");
				return false;			
			}
			return( true );
		
		}
		function submitlogin()
		{
		  document.loginform.submit();
		}
		</script> 
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
			<div id="contentbox" style="padding-top:112px;">
				<div id="stylized" class="myform">
				<form id="newpassform" name="newpassform" method="post" action="editacc_handler.php" onsubmit="return(validate());" autocomplete="off">
				<h1>Edit Account</h1>
				<p>Change your accounts password.</p>

				<label>Current Password
				<span class="small">Case sensitive</span>
				</label>
				<input type="password" name="currentpassword" id="currentpassword" autocomplete="off"/>

				<label>New Password
				<span class="small">Min. size 6 chars</span>
				</label>
				<input type="password" name="newpassword" id="newpassword" />
				
				<label>Confirm Password
				<span class="small">retype your new password</span>
				</label>
				<input type="password" name="confirmpassword" id="confirmpassword" />
				
				<button type="submit" value="Submit" style="margin-top:9px;">Submit</button>
				<div class="spacer"></div>

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