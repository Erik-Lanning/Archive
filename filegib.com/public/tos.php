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
				<div><h1>Terms of Service</h1></div>
			</center>
			<div id="tos" style="width:700px;padding-left:28%;">
				<p>The Filegib site (hereinafter: "Filegib.com") renders web hosting services for its users based on the following provisions.
				</p>
				<div class="section">
				<div class="section">
				<h2>1. Introduction</h2>
				<p>Filegib.com provides its users with an infrastructure, which enables the user to save electronic files on the Filegib.com internet servers. After selecting a file, the user receives a unique download link, through which the user's file immediately can be downloaded through the internet. After selecting the file, it is saved on the Filegib.com internet servers for download at any time using the unique download link. Basic services provided by Filegib.com are free- of-charge. Other services, which add features and functionality to the basic services, are provided for a charge.
				</p>
				</div>
				<div class="section">
				<h2>2. File Upload and Content Rules</h2>
				<p>The size of each individual file saved on the Filegib.com internet servers may not exceed 2GB.</p>
				<p>The users are permitted to save their files on the Filegib.com internet servers provided that these files fulfill Filegib.com's requirements as to their use and content (in this section 2, "Content" means any communications, images, photographs, text, video, audiovisual works, drawings, paintings, and all other material and information that a user uploads or transmits through the Filegib.com internet servers, or that other users upload or transmit).</p>
				<p>BY SAVING CONTENT ON THE Filegib.com INTERNET SERVERS, THE USERS GRANT TO Filegib.com, INCLUDING WITHOUT LIMITATION Filegib.com'S SUCCESSORS AND ASSIGNS, A NON-EXCLUSIVE, PERPETUAL, IRREVOCABLE, SUB-LICENSABLE, TRANSFERABLE, WORLDWIDE, PAID-UP RIGHT TO STORE AND REPRODUCE SUCH CONTENT ON THE Filegib.com INTERNET SERVERS AND TO ACCESS THE USERS' COMPUTER FOR THE PURPOSE OF ACCESSING THE CONTENT THAT THE USERS HAVE SAVED WITH Filegib.com.</p>
				<p>A USER IS NOT PERMITTED TO SAVE ON THE Filegib.com INTERNET SERVERS ANY CONTENT THAT THE USER HAS NOT OBTAINED BY LEGAL MEANS AND/OR THAT CANNOT LEGALLY BE DISTRIBUTED BY THE USER (E.G. CONTENT THAT VIOLATES ANY COPYRIGHTS, INSTRUCTIONS FOR CRIMINAL OFFENSES AGAINST PUBLIC ORDER, CHILD PORNOGRAPHY, RACIST OR VIOLENCE-GLORIFYING CONTENT, ETC.).</p>
				<p>BY SAVING CONTENT ON THE Filegib.com INTERNET SERVERS, THE USERS AGREE THAT THEY MAY NOT UPLOAD OR OTHERWISE TRANSMIT TROUGH Filegib.com ANY CONTENT THAT IS SUBJECT TO ANY THIRD PARTY RIGHTS WITHOUT BEING GRANTED PERMISSION BY SUCH THIRD PARTIES TO DO SO. BY SAVING CONTENT ON THE Filegib.com INTERNET SERVERS, THE USERS ACKNOWLEDGE AND AGREE THAT Filegib.com WILL IN NO WAY BE SUBJECT TO ANY OBLIGATION, WHETHER OF CONFIDENTIALITY, ATTRIBUTION OR OTHERWISE, REGARDING THE CONTENT.</p>
				<p>Filegib.com RESERVES THE RIGHT TO IMMEDIATELY BLOCK CONTENT CONTRARY TO THE ABOVE AND TO DELETE CONTENT, INCLUDING CONTENT, WHICH ARE IDENTICAL TO PREVIOUSLY DELETED CONTENT.</p>
				<p>Filegib.com IS ENTITLED TO CEASE WITHOUT NOTICE THE SERVICES (PAID OR UNPAID) TO A USER, WHO INFRINGES Filegib.com'S UPLOAD AND CONTENT RULES, INCLUDING TO BLOCK THE ACCESS OF THE SAID USER AND/OR TO DELETE THE ACCOUNTS OF THE SAID USER, INCLUDING ALL CONTENT.</p>
				<p>Filegib.com claims no ownership rights in the users' Content, and Filegib.com neither does nor can pre-screen or monitor Content. Filegib.com does not assume any responsibility or liability for Content of any kind. Filegib.com reserves the right, at all times and in the sole discretion of Filegib.com, to disclose any Content for any reason, including without limitation (i) to satisfy any applicable law, regulation, legal process or governmental request, (ii) to enforce the Terms of use or any other agreement, (iii) to protect the legal rights and remedies of Filegib.com, and/or (iv) to report a crime or other offensive or threatening behavior.</p>
				<p>Filegib.com SHALL NOT BE LIABLE IN ANY MANNER FOR THE DESTRUCTION, DELETION, MODIFICATION, IMPAIRMENT, HACKING OF OR ANY OTHER DAMAGE OR LOSS OF ANY KIND CAUSED TO CONTENT, INCLUDING, BUT NOT LIMITED TO, DELETION OF CONTENT UPON THE TERMINATION OR EXPIRATION OF A USER'S ACCOUNT.</p>
				</div>
				<div class="section">
				<h2>3. The Account</h2>
				<p>An account may be used by one person/entity only unless otherwise authorised by Filegib.com. The users are obligated to keep the user names and passwords of their accounts secret. It is not allowed to forward user names and passwords to third parties. The sale of Filegib.com accounts (with or without payable services) whether offered with other products and services or not requires the authorisation of Filegib.com. Filegib.com reserves the right to block accounts, which are used by several persons without the authorisation of Filegib.com or which have been sold without the authorisation of Filegib.com. Any damages which arise through the forwarding of passwords or unauthorised access to accounts shall not be reimbursed by Filegib.com.</p>
				<p>A user may at any time delete his/her account and/or individual files saved on the Filegib.com internet servers.</p>
				</div>
				<div class="section">
				<h2>4. Services Free of Charge</h2>
				<p>At its discretion, Filegib.com shall provide its users with storage capacities and service administration. Filegib.com is entitled to temporarily prohibit the saving of new files, set limits for the maximum possible file sizes, set limits for the maximum possible files stored by a user and delete files after a period with no download of such files. In order to clean its file storage, Filegib.com is entitled to delete files which have not been accessed for a longer period of time. However, this deletion shall only take place after minimum 30 days have passed since the file was uploaded, and if the user does not have an account.</p>
				<p>Users of the Filegib.com services shall have the option of registering free-of-charge. Through this registration, they can expand the features and functions of the Filegib.com services and view and manage all files, which have been uploaded using this account.</p>
				</div>
				<div class="section">
				<h2>5. Paid Services</h2>
				<p>Users of the Filegib.com services also have the option of expanding their accounts with payable packages, so that they can use additional features and functionality.</p>
				<p>Filegib.com provides information on the Filegib.com website about available paid packages, the services contained within the packages, the prices and payment options and additional usage conditions of each package. Filegib.com is entitled to remove individual packages at any time, to change the services contained within the packages or to offer new packages as part of its services. Users, who have already paid for a package that is no longer available, are entitled to terminate their contract without notice within one month of receiving notification of the change and shall receive a proportionate reimbursement of the package price they have already paid.</p>
				</div>
				<div class="section">
				<h2>6. Payment</h2>
				<p>To acquire the paid services, Filegib.com provides its users with the option of payment using credit card payment.</p>
				<p>Users, who choose to pay with credit card, are forwarded to an SSL-encoded internet site of the payment provider, through which they can make the payment using authorized credit cards. The payment provider will then return the user to the Filegib.com internet site. As soon as payment provider has confirmed the receipt of payment to Filegib.com, Filegib.com shall provide the user with his/her services. To secure continued service, the user has the option to select recurring payments using credit card. It is the obligation of the user to keep credit card details up to date with the payment provider.</p>
				<p>Filegib.com hereby refers expressively to the fact that it will immediately block accounts if the prepaid credit acquired for these accounts is reversed, if charges or credit card debits "bounce" or if the payment provider reverses a payment as a preventative measure due to irregularities. Filegib.com is not in the position to clarify the background for reversed payments and will refer the user to his/her bank or selected payment provider in the case of such payment problems. Should an account, which has been blocked due to a reverse payment, be released again, Filegib.com is entitled to charge an administrative fee of maximum of $35 USD from the user.</p>
				</div>
				<div class="section">
				<h2>7. Limitation of Liability</h2>
				<p>Filegib.com WILL NOT BE LIABLE TO ANY USERS OF Filegib.com SERVICES FOR ANY: LOSS OF BUSINESS; LOSS OF REVENUE; LOSS OF PROFITS; LOSS OF ANTICIPATED SAVINGS; WASTED EXPENDITURE, LOSS OF PRIVACY AND/OR LOSS OF DATA; AND/OR ANY OTHER LOSS DAMAGE WHICH ARISE OUT OF OR ARE RELATED TO YOUR USE OF THE SERVICES.</p>
				<p>Filegib.com SHALL NOT BE LIABLE TO ANY PERSON FOR ANY LOSS OR DAMAGE, WHICH MAY ARISE FROM THE USE OR MISUSE OF ANY OF THE INFORMATION CONTAINED IN ANY OF THE MATERIALS STORED ON THE Filegib.com INTERNET SERVERS.</p>
				</div>
				<div class="section">
				<h2>8. Miscellaneous</h2>
				<p>Filegib.com will inform users of changes to the Terms.</p>
				<p>If the user has acquired a paid service and Filegib.com changes this service to the effect that the advantages of this service are reduced, the user shall be entitled to terminate the commitment to the paid service within a period of four weeks after receiving notification of the changes. If the user does not make use of his/her right to terminate the commitment to the paid service, the changes shall be deemed accepted and shall becomeeffective components of the paid service.</p>
				<p>Should a clause of a contract with a user or a condition in the Terms be or become wholly or partially ineffective, the validity of the contract or the Terms shall remain unaffected by this. The ineffective clause/condition shall be replaced by a clause/condition that serves the purpose of the ineffective clause/condition in a legally effective manner. This shall also apply in the case that there is a loophole.</p>
				<p>Any information on the users, such as names, addresses etc., that the users may be asked to provide to Filegib.com, is solely gathered to enable Filegib.com to identify and get in contact with its users in relation to the services provided by Filegib.com.</p>
				<p>Filegib.com only uses so-called first-party cookies which are cookies created and utilised by Filegib.com and only for web trends analysis. Filegib.com does not share cookie data or any other related user behavior with any third parties.</p>
				<p>If you write programs aiming to violate the Terms, you may be made liable for any losses occurred to Filegib.com.</p>
				</div>
				</div>				
				<div class="section claims">
				<div class="section">
				<h2>Claims for copyright infringement</h2>
				<p>
				If you are a copyright owner or agent thereof and believe that content posted on the Filegib.com internet servers infringes upon your copyright, please submit notice, pursuant to the Digital Millennium Copyright Act (17 U.S.C. S 512(c)) to our copyright agent with the following information:
				</p>
				<ul>
				<li>(a) an electronic or physical signature of the person authorized to act on behalf of the owner of the copyright;</li>
				<li>(b) a description of the copyrighted work that you claim has been infringed;</li>
				<li>(c) the URL of the location on our website containing the material that you claim is infringing;</li>
				<li>(d) your address, telephone number, and email address;</li>
				<li>(e) a statement by you that you have a good faith belief that the disputed use is not authorized by the copyright owner, its agent, or the law; and</li>
				<li>(f) a statement by you, made under penalty of perjury, that the above information in your notice is accurate and that you are the copyright owner or authorized to act on the copyright owner's behalf.</li>
				</ul>
				<p>
				Our copyright agent can be reached by email at copyright@filegib.com
				</p>
				</div>
				<br/>
				<br/>
				<br/>
				<br/>
				<br/>
				<br/>
				<br/>
				</div>
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