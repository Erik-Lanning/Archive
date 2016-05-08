<?php require "globals.php";?>
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
			<div id="contentbox" style="margin-top:20px; overflow:auto; height:800px;">
			<center>
				<div><h1>Privacy Policy</h1></div>
			</center>
			<div style="width:700px;padding-left:28%; font-family:arial">
				<strong>What information do we collect?</strong>
				<br />
				<br />
				We collect information from you when you register on our site, fill out a form or upload a file.  
				<br />
				<br />
				When ordering or registering on our site, as appropriate, you may be asked to enter your: name, e-mail address, mailing address, phone number or credit card information. You may, however, visit our site anonymously.<br /><br />Google, as a third party vendor, uses cookies to serve ads on your site.
				Google's use of the DART cookie enables it to serve ads to your users based on their visit to your sites and other sites on the Internet.
				Users may opt out of the use of the DART cookie by visiting the Google ad and content network privacy policy..
				<br />
				<br />
				<strong>What do we use your information for?</strong> 
				<br />
				<br />Any of the information we collect from you may be used in one of the following ways: 
				<br />
				<br />; To improve our website
				<br />(we continually strive to improve our website offerings based on the information and feedback we receive from you)
				<br />
				<br />; To process transactions
				<br />
				<blockquote>
				Your information, whether public or private, will not be sold, exchanged, transferred, or given to any other company for any reason whatsoever, without your consent, other than for the express purpose of delivering the purchased product or service requested.
				</blockquote>
				<br />; To send periodic emails
				<br />
				<br />The email address you provide may be used to send you information, respond to inquiries, and/or other requests or questions.
				<br />
				<br />
				<strong>How do we protect your information?</strong>
				<br />
				<br />
				We implement a variety of security measures to maintain the safety of your personal information when you place an order or enter, submit, or access your personal information. 
				<br />
				<br />We offer the use of a secure server. All supplied sensitive/credit information is transmitted via Secure Socket Layer (SSL) technology and then encrypted into our Payment gateway providers database only to be accessible by those authorized with special access rights to such systems, and are required to?keep the information confidential.
				<br />
				<br />After a transaction, your private information (credit cards, social security numbers, financials, etc.) will not be kept on file for more than 60 days.
				<br />
				<br />
				<strong>Do we use cookies?</strong>
				<br />
				<br />
				Yes (Cookies are small files that a site or its service provider transfers to your computers hard drive through your Web browser (if you allow) that enables the sites or service providers systems to recognize your browser and capture and remember certain information
				<br />
				<br />
				We use cookies to help us remember and process the items in your shopping cart and understand and save your preferences for future visits.
				<br />
				<br />
				<strong>Do we disclose any information to outside parties?</strong>
				<br />
				<br />
				We do not sell, trade, or otherwise transfer to outside parties your personally identifiable information. This does not include trusted third parties who assist us in operating our website, conducting our business, or servicing you, so long as those parties agree to keep this information confidential. We may also release your information when we believe release is appropriate to comply with the law, enforce our site policies, or protect ours or others rights, property, or safety. However, non-personally identifiable visitor information may be provided to other parties for marketing, advertising, or other uses.
				<br />
				<br />
				<strong>Third party links</strong>
				<br />
				<br />
				Occasionally, at our discretion, we may include or offer third party products or services on our website. These third party sites have separate and independent privacy policies. We therefore have no responsibility or liability for the content and activities of these linked sites. Nonetheless, we seek to protect the integrity of our site and welcome any feedback about these sites.
				<br /><br /><strong>California Online Privacy Protection Act Compliance</strong><br /><br />Because we value your privacy we have taken the necessary precautions to be in compliance with the California Online Privacy Protection Act. We therefore will not distribute your personal information to outside parties without your consent.
				<br /><br /><strong>Childrens Online Privacy Protection Act Compliance</strong> <br /><br />We are in compliance with the requirements of COPPA (Childrens Online Privacy Protection Act), we do not collect any information from anyone under 13 years of age. Our website, products and services are all directed to people who are at least 13 years old or older.
				<br /><br /><strong>Online Privacy Policy Only</strong> <br /><br />This online privacy policy applies only to information collected through our website and not to information collected offline.
				<br /><br /><strong>Terms and Conditions</strong> <br /><br />Please also visit our Terms and Conditions section establishing the use, disclaimers, and limitations of liability governing the use of our website at <a href="http://filegib.com/tos.php">http://filegib.com/tos.php</a>
				<br /><br /><strong>Your Consent</strong> <br /><br />By using our site, you consent to our <a style='text-decoration:none; color:#3C3C3C;' href='http://www.freeprivacypolicy.com/' target='_blank'>web site privacy policy</a>.
				<br /><br /><strong>Changes to our Privacy Policy</strong> <br /><br />If we decide to change our privacy policy, we will post those changes on this page, and/or update the Privacy Policy modification date below. 
				<br /><br />This policy was last modified on 4/19/2013
				<br /><br /><strong>Contacting Us</strong> <br /><br />If there are any questions regarding this privacy policy you may contact us using the information below. <br /><br />http://filegib.com/contact.php<br />contact@filegib.com<br /><br /><span></span><span></span>
				<br/><br/>
				<br/><br/>
				<br/><br/>
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