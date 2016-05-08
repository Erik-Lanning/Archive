<?php
	//url_handler.php by Erik Lanning on 2/9/2013
	//Dynamic URL handler, uses $_GET or $_POST to display the file
	//Global imports go here:
	//
	if(isset($_GET['id'])) {
		require_once('globals.php');
		if(strlen($_GET['id']) > 9) {
			//redirect to error page
			header( 'Location: http://www.filegib.com/' );
		}
		$website_url = cleanInput($_GET['id']);
		if(substr($website_url, 0, 3) == "adv") {
			$website_url = $mysqli->real_escape_string($website_url);
			$query = "SELECT * FROM advfileindex WHERE url_id = '$website_url' LIMIT 1";
			$result = $mysqli->query($query);		
		} else {
			$website_url = $mysqli->real_escape_string($website_url);
			$query = "SELECT * FROM fileindex WHERE url_id = '$website_url' LIMIT 1";
			$result = $mysqli->query($query);
		}
		if(!($result->num_rows > 0)) {
			header( 'Location: http://www.filegib.com/' );	
		}
	} else {
		//redirect to error page
	}
	
	/*$website_url = sanitize($_GET['id']);
	if ($website_url > greater than 6 digits) {
		//redirect to error page
	} */	
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
		<link href="http://vjs.zencdn.net/c/video-js.css" rel="stylesheet">
		<script src="http://vjs.zencdn.net/c/video.js"></script>
		<script type="text/javascript" src="<?php echo $rootdir; ?>/plugins/audioplayer/audio-player.js"></script>
		<script type="text/javascript">
		function submitlogin()
		{
		  document.loginform.submit();
		}
		</script>
		<style>
		#file_description {
			position: absolute;
			margin-right: 10%;
			margin-left: 67%;
			border-radius: 15px; border-style:solid; border-width: thin;
			width: 500px;
			height: 85px;
			text-align: center;
			padding: 10px;
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
		<div id="contentbox" style="padding-top:500px; overflow:auto;">		
			<?php
				//Get MySQL server calls
				if(substr($website_url, 0, 3) == "adv") {
					$query = "SELECT url_id, file_name, file_hash, file_type, file_views, file_path, file_size, file_title, file_description, file_keywords, file_password FROM advfileindex WHERE url_id = '$website_url'";
					$view_query = "UPDATE advfileindex SET file_views = file_views+1 WHERE url_id = '$website_url'";
					$result = $mysqli->query($query);
					$update_views = $mysqli->query($view_query);
					$mysqli->close();
					$count = 10;
				} else {
					$query = "SELECT url_id, file_name, file_hash, file_type, file_views, file_path, file_size FROM fileindex WHERE url_id = '$website_url'";
					$view_query = "UPDATE fileindex SET file_views = file_views+1 WHERE url_id = '$website_url'";
					$result = $mysqli->query($query);
					$update_views = $mysqli->query($view_query);
					$mysqli->close();
					$count = 7;
				}
				if($result) {
					$divtype = "";
					$row = $result->fetch_row();
						for($i=0; $i < $count; ++$i) { //do stuff with the returned SQL data
							switch($i) {
								case 0: //url_id
									$local_url_id = "<div id='url_id'>Download Link: http://filegib.com/".$row[$i]."</div>";
									break;
								case 1: //file_name
									$local_file_name = "<div id='file_name'>File Name: ".$row[$i]."</div>";
									break;								
								case 2: //file_hash
									$local_file_hash = "<div id='file_hash'>File Hash: ".$row[$i]."</div>";
									break;
								case 3: //file_type, this section deals with plugins.
									//google doc supported files
									foreach($gdocfiles as $element) {
										if($row[$i] == $element) {
											$local_plugin = "<iframe src=\"http://docs.google.com/viewer?url=".urlencode($row[5])."&embedded=true\" width=\"1200\" height=\"525\" style=\"border: none;\" id=\"contentplugin\"></iframe>";										
											$divtype = "googleplugin";
										}
										continue;
									}
									//image files
									foreach($images as $element) {
										if($row[$i] == $element) {
											$local_image = "<div id='file_img'><img id=\"pagefile\" src=\"".$row[5]."\" onclick=\"document.location=this.src\" /></div>";
											$divtype = "imageplugin";
											continue;
										}
									}	
									//music files
									foreach($music_files as $element) {
										if($row[$i] == $element) {
											$local_music_file = "
											<object type=\"application/x-shockwave-flash\" data=\"plugins/audioplayer/dewplayer-bubble-vol.swf\" width=\"250\" height=\"65\" id=\"dewplayer\" name=\"dewplayer\"> <param name=\"wmode\" value=\"transparent\" /><param name=\"movie\" value=\"plugins/audioplayer/dewplayer-bubble-vol.swf\" /> <param name=\"flashvars\" value=\"mp3=up/".$row[0]."/".$row[1]."&amp;autoreplay=1&amp;showtime=1&amp;volume=50\" /> </object>
											<div id='mp3padding'></div>
											";
											$divtype = "musicplugin";
										}
										continue;
									}
									foreach($video_files as $element) {
										if($row[$i] == $element) {
											if($row[$i] == "mp4") {
												$vidtype = 'video/mp4';
											}
											if($row[$i] == "webm") {
												$vidtype = 'video/webm';
											}
											if($row[$i] == "ogg") {
												$vidtype = 'video/ogg';
											}
											$local_video_file = "
											<video id=\"videoplayer\" class=\"video-js vjs-default-skin\" controls
											  preload=\"auto\" width=\"911\" height=\"444\" poster=\"\"
											  data-setup=\"{}\">
											  <source src=\"".$row[5]."\" type='".$vidtype."'>
											</video>
											<br/>
											<br/>
											";
											$divtype = "videoplugin";
										
										}
										continue;
									}
									global $supported_fimages;
									foreach($supported_fimages as $element) {
										if($row[$i] == $element) {
											$local_file_icon = "<div id='file_icon' style='padding-top:10%;'><img src=\"".$rootdir."/img/fileicons/".$element.".png\" width='150' height='170' /></div>";
										}
										if(!isset($local_file_icon)) {
											$local_file_icon = "<div id='file_icon' style='padding-top:10%;'><img src=\"".$rootdir."img/fileicons/_blank.png\" width='150' height='170' /></div>";
										}
									}
									//high risk files
									foreach($highrisk_files as $element) {
										if($row[$i] == $element) {
											//provide virus scan link
											
											if($row[$i] == "exe") {} //exe icon
											if($row[$i] == "zip") {} //zip icon
											if($row[$i] == "rar") {} //rar icon
											if($row[$i] == "msi") {} //msi icon
										}
									}
									//Default, no plugins found.
									//echo "<div id='file_type'><a href=\"".$row[5]."\"><img src=\"/img/genericfile.png\" /></a></div>";
									break;
								case 4: //file_views
									$local_file_views = "<div id='file_views'>Views: ".$row[$i]."</div>";
									break;
								case 5: //file_path
									$local_file_path = "<div id=\"downloadbutton\"><a href=\"".$row[5]."\" ><img src=\"".$rootdir."/img/downloadbutton.png\" onmouseover=\"this.src='".$rootdir."/img/downloadhover.png';\" onmouseout=\"this.src='".$rootdir."/img/downloadbutton.png';\" /></a></div>";
									break;
								case 6: //file_size
									$local_file_size = "<div id='file_size'>File Size: ".$row[$i]."</div>";
									break;
								case 7: //file title
									$local_file_title = "<div id='file_title'><h3>".$row[$i]."</h3></div>";
								case 8: //file description
									$local_file_description = "<div id='file_description'>".$row[$i]."</div>";
								case 9: //file keywords
									$local_file_keywords = "<div id='file_keywords'>Keywords: ".$row[$i]."</div>";
								case 10: //file password
									$local_file_password = $row[$i];
								default:
									break;
							}
						}
						//Print the file info in whatever order needed:
						$no_plugin_support = 0;
						switch($divtype) {
							case "videoplugin": echo '<div id="videodiv">'; break;
							case "soundplugin": echo '<div id="sounddiv">'; break;
							case "googleplugin": echo '<div id="googlediv">'; break;
							case "imageplugin": echo '<div id="emperordiv">'; break;
							case "": default: echo '<div id="noplugindiv">'; break;
						}
						if(isset($local_file_title)) {
							echo $local_file_title;
						}
						if(isset($local_image)) {
							echo $local_image;
							$no_plugin_support = 1;
						}
						if(isset($local_video_file)) {
							echo $local_video_file;
							$no_plugin_support = 1;
						}
						if(isset($local_plugin)) {
							echo $local_plugin;
							$no_plugin_support = 1;
						}
						if(isset($local_music_file)) {
							echo $local_music_file;
							$no_plugin_support = 1;
						} 
						//file is not supported by plugins: display a file icon instead.
						if(isset($local_file_icon) && !($no_plugin_support)) {
							echo $local_file_icon;
						}
						echo '
							<div id="filecontentbox">
								<center>';
						echo $local_url_id . $local_file_name . $local_file_size . $local_file_path . $local_file_views;
						if(isset($local_file_keywords)) {
							echo $local_file_keywords;
						}
						echo '	</center>
						</div>';
						echo '</div>';
						if(isset($local_file_description)) {
							echo $local_file_description;
						}
				}
			?>
			<div id="sponsored links">	
				<!---ads-->
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