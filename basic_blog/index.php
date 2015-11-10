<?php
include_once 'dbconfig.php';
//<input type = "hidden" name = "MAX_FILE_SIZE" value="2000000">
?>
<!DOCTYPE html>
<!DOCTYPE html>
<html>
<head>
<title> File Uploader</title>
</head>
<body>
	<label>File uploader</label>
	<div id = "uploadForm">
		<form action="upload.php" method = "post" enctype = "multipart/form-data">
		<input type = "file" name = "userfile" id= "userfile"/>
		<button type = "submit" name = "upload_btn">Upload</button>			
		</form>
		<br/>
		<?php
		if(isset($_GET['success'])){
			?>
			<label>
				File Uploaded successfully
				<a href="view.php">click here to review.</a>
			</label>
			<?php
		}
		else if(isset($_GET['fail']))
		{
			?>
			<label>Problem while file uploading</label>
			<?php
		}
		else
		{
			?>
			<label>
				Try to upload any files
			</label>
			<?php
		}
		?>
	</div>
</body>
</html>