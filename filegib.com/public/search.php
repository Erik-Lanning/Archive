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
		<style>
		#filetable {
			padding: 35px;
			overflow: auto;
		}
		.boxoutline {
			 border-radius: 5px;
			 border-style: solid; 
			 border-width: thin;
			 width: 400px;
			 margin: 25px;
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
			<div id="contentbox" style="margin-top:20px; overflow:auto; height:800px;">
			<center>
				<div><h1>Search Results</h1></div>
			</center>
				<div style="font-family:arial">
					<?php
						//search_engine.php by Erik Lanning, original code from Zvonko Biškup on [6/16/2013]
						//Takes search inputs from the search bar, runs them through the database, and returns any results
							function makebox($array/*, xcoordinate, $ycoordinate*/) {
								//9 is the number of row elements
								for($i=0; $i < 9; ++$i) {
									switch($i) {
										case 0: //url_id
											$local_url_id = "<div id='url_id'>Download Link:<br/><a href=\"http://filegib.com/".$array[$i]."\">http://filegib.com/".$array[$i]."</a></div>";
											$local_file_id = $array[$i];
											break;
										case 1: //file_name
											$local_file_name = "<div id='file_name'>File Name:<br/> ".chunk_split($array[$i], 10)."</div>";
											break;								
										case 2: //file_hash
											$local_file_hash = "<div id='file_hash'>File Hash: ".$array[$i]."</div>";
											break;
										case 3: //file_type, this section deals with plugins.
											global $supported_adv_fimages;
											foreach($supported_adv_fimages as $element) {
												if($array[$i] == $element) {
													$local_file_icon = "<div id='file_icon' style='padding-top:10%; float:left;'><img src=\"".$rootdir."img/fileicons/".$element.".png\" width='150' height='170' /></div>";
												}
												if(!isset($local_file_icon)) {
													$local_file_icon = "<div id='file_icon' style='padding-top:10%; float:left;'><img src=\"".$rootdir."img/fileicons/_blank.png\" width='150' height='170' /></div>";
												}
											}
											break;
										case 4: //file_views
											$local_file_views = "<div id='file_views'>Views: ".$array[$i]."</div>";
											break;
										case 5: //file_path
											break;
										case 6: //file_size
											$local_file_size = "<div id='file_size'>File Size: ".$array[$i]."</div>";
											break;
										case 7: //file title
											$local_file_title = "<div id='file_title'><h3>".$array[$i]."</h3></div>";
											break;
										case 8: //file description
											$local_file_description = "<div id='file_description'>".$array[$i]."</div>";
											break;
										case 9: //file keywords
											$local_file_keywords = "<div id='file_keywords'>Keywords: ".$array[$i+1]."</div>";
											break;
										case 10: //file password
											$local_file_password = $row[$i];
											break;
										default:
											break;						
									}
								}
									echo "
										<div class=\"boxoutline\" id=\"".$local_file_id."\" >
											";
									echo $local_file_icon;
									echo $local_url_id . $local_file_name . $local_file_views . $local_file_size;
									echo "<div class=\"deletebutton\" id=\"padding\" style=\"padding: 45px;\"></div>";
									echo '	
									</div>';
								return;
							}
							//if we got something through $_POST
							if (isset($_POST['searchinputbox'])) {
								// sanitize user input
								$word = cleanInput($_POST['searchinputbox']);
								if(strlen($word) <= 0) {
									echo "
									<br/>
									<br/>
									<br/>
									<br/>
									<br/>
									<br/>
									<div style=\"font:23px arial; margin-left: 35%;\" >No search input entered, try researching.</div>			
									";
									exit();
								}
								$word = $mysqli->real_escape_string($word);
								// build your search query to the database
								//$sql = "SELECT url_id, file_name, file_type, file_size FROM fileindex, advfileindex WHERE file_name LIKE '%" . $word . "%' ORDER BY file_name LIMIT 10";
								$sql = "SELECT url_id, file_name, file_hash, file_type, file_views, file_path, file_size FROM fileindex WHERE file_name LIKE '%" . $word . "%' ORDER BY file_views LIMIT 35";
								// get results
								if( ($result = $mysqli->query($sql)) && ($num_rows = $result->num_rows > 0) ) {
									$i = 0;
									echo '<table>';
										while( $all_rows = $result->fetch_row() ) {
											if($all_rows) {
													if($i % 3 === 0) echo "\n<tr>";
													echo "<td>";
													makebox($all_rows/*, $posx, $posy*/);
													echo "</td>";
													if($i % 3 === 2) echo "</tr>";
													$i++;
											}
										}
									if($i % 3 > 0) echo "</tr>"; 
									echo '</table>';
									echo '<br/><br/><br/><br/><br/>';
								} else {
									echo "
									<br/>
									<br/>
									<br/>
									<br/>
									<br/>
									<br/>
									<div style=\"font:23px arial; margin-left: 35%;\" >No search results found for this query, sorry.</div>				
									";
								}
							} else {
								echo "
								<br/>
								<br/>
								<br/>
								<br/>
								<br/>
								<br/>
								<div style=\"font:23px arial; margin-left: 35%;\" >No search input entered, try researching.</div>			
								";
							}
					?>
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