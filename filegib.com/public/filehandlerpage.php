<?php 
	require "globals.php";
	if(!isset($_SESSION['email'])) {
			echo "Please relog, your session has expired.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/">';
			exit();	
	}
	if(isset($_SESSION['contributer_status'])) {
		if($_SESSION['contributer_status'] != 1) {
			echo "This page is for contributers only, sorry.<br/>";
			echo "Redirecting in 5 seconds.";
			echo '<meta http-equiv="refresh" content="5; url=http://filegib.com/">';
			exit();			
		}
	} else {
			echo "This page is for contributers only, sorry.<br/>";
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
		<!--JavaScript Plugins-->
		<script type="text/javascript" src="http://code.jquery.com/jquery-1.7.2.min.js"></script>
		<script language="JavaScript" type="text/javascript">
		function submitlogin()
		{
		  document.loginform.submit();
		}
		function deletefile(fileid) {
			if (confirm('Are you sure you want to delete this file?')) {
				var xmlhttp;
				if (window.XMLHttpRequest)
				  {// code for IE7+, Firefox, Chrome, Opera, Safari
				  xmlhttp=new XMLHttpRequest();
				  }
				else
				  {// code for IE6, IE5
				  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
				  }		

					xmlhttp.open("POST","deletecfile.php",true);
					xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
					xmlhttp.send("fileid="+fileid);
				delete_element = document.getElementById(fileid);
				delete_element.parentNode.removeChild(delete_element);
			}
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
					<div><h1>Your Files</h1></div>
				</center>			
				<?php
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
								case 5: //file_path
									break;
								case 6: //file_size
									$local_file_size = "<div id='file_size'>File Size: ".$array[$i]."</div>";
								case 7: //file title
									$local_file_title = "<div id='file_title'><h3>".$array[$i]."</h3></div>";
								case 8: //file description
									$local_file_description = "<div id='file_description'>".$array[$i]."</div>";
								case 9: //file keywords
									$local_file_keywords = "<div id='file_keywords'>Keywords: ".$array[$i+1]."</div>";
								case 10: //file password
									$local_file_password = $row[$i];
								default:
									break;						
							}
						}
							echo "
								<div class=\"boxoutline\" id=\"".$local_file_id."\" >
									";
							echo $local_file_icon;
							echo $local_file_title . $local_url_id . $local_file_name . $local_file_path . $local_file_views;
							if(isset($local_file_keywords)) {
								echo $local_file_keywords;
							}
							echo "<div class=\"deletebutton\" id=\"".$local_file_id."\" onClick=\"deletefile(this.id)\" style=\"padding: 35px;\"><a href=\"#\">Delete File</a></div>";
							echo '	
							</div>';
						return;
					}
					//get the users files
					$email = $_SESSION['email'];
					$query = "SELECT url_id, file_name, file_hash, file_type, file_views, file_path, file_size, file_title, file_description, file_keywords, file_password FROM advfileindex WHERE users_email='$email'";
					if($executequery = $mysqli->query($query)) {
						$i = 0;
						echo '<table>';
							while( $all_rows = $executequery->fetch_row() ) {
								if($all_rows) {
										if($i % 3 === 0) echo "\n<tr>";
										echo "<td>";
										makebox($all_rows/*, $posx, $posy*/);
										echo "</td>";
										if($i % 3 === 2) echo "</tr>";
										$i++;
								} else {
									echo "<center><h2><a href=\"/advancedupload.php\">You have no files uploaded yet.</a></h2></center>";
								}
							}
						if($i % 3 > 0) echo "</tr>"; 
						echo '</table>';
						echo '<br/><br/><br/><br/><br/>';
					}
				?>
			</div>
		<div id="footer">
				<div id="bottomlist">
					 <a href="<?php echo $rootdir; ?>/policy.php">Privacy Policy</a>
					 <a href="<?php echo $rootdir; ?>/tos.php">Terms of Use</a>
					 <a href="<?php echo $rootdir; ?>/contact.php">Contact</a>
				</div>
		</div>
	</body>
</html>