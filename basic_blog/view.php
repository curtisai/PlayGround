<?php
include_once 'dbconfig.php';
?>
<!DOCTYPE html>
<html>
<head>
	<title>File Uploader</title>
</head>
<body>
<div>
	<table width="80%" border="1">
		<tr>
			<th colspan="4">your uploads...
			<label><a href="index.php">upload new files...</a></label>
			</th>
		</tr>
		<tr>
			<td>File Name</td>
			<td>File Type</td>
			<td>File Size(KB)</td>
			<td>File View</td>
		</tr>
		<?php
		$sql = "SELECT * FROM upload";
		$result_set = mysql_query($sql);
		while($row = mysql_fetch_array($result_set)){
			?>
			<tr>
				<td><?php echo $row['name'] ?> </td>
				<td><?php echo $row['type'] ?> </td>
				<td><?php echo $row['size'] ?> </td>
				<td><a href="download.php?id=<?php echo $row['id']; ?>">View</a></td>
			</tr>
			<?php
		}
		?>
	</table>
</div>
</body>
</html>
?>