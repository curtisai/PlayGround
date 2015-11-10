<?php
include_once 'dbconfig.php';
if(isset($_POST['upload_btn'])){
	$file = $_FILES['userfile']['name'];
	$file_loc = $_FILES['userfile']['tmp_name'];
	$file_size = $_FILES['userfile']['size'];
	$file_type = $_FILES['userfile']['type'];

	$fp=fopen($file_loc, 'r');
	$content = fread($fp, filesize($file_loc));
	$content = addslashes($content);
	fclose($fp);
	$folder = "./uploads/";

	$new_size = $file_size/1024;

	$file = mysql_real_escape_string($file);
	if(move_uploaded_file($file_loc, $folder.$file)){
		$sql = "INSERT INTO upload(name,type,size,content) VALUES('$file','$file_type','$new_size','$content')";
		mysql_query($sql);
		?>
		<script>
		alert('successfully uploaded');
		window.location.href = 'index.php?success';
		</script>
		<?php
	}
}
else{
	?>
	<script>
	alter('error while uploading file');
	window.location.href = 'index.php?fail';
	</script>
	<?php
}
?>