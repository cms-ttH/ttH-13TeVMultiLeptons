<!doctype html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Directory Contents</title>

<style type="text/css">
   * {
    font-family: Ubuntu,sans-serif;   
	padding:0;
	margin:0;
	color: #663300;    
}

body {
	color: #333;
	padding: 50px;
	background: #253342;
}

h1 {
	text-align: left;
	padding: 20px 0 12px 0;
    color: white;
}

.search {
 padding: 6px 6px 6px 10px;
 margin:3px;
}

.rounded {
  border-radius:10px;
 -moz-border-radius:10px;
 -webkit-border-radius:10px;
}

.photo-link{ text-align: center; padding:5px; border-radius:0.5em; margin:5px; border:1px solid #ccc; display:block; width:300px; float:left; background: white }                                                       

table {
	border-collapse: collapse;
    border-spacing: 0;
	width: 88.3%;
	margin: 15px 0;
}

 th:first-child {
  -moz-border-radius: 10px 0 0 0;
  -webkit-border-radius: 10px 0 0 0;
      border-radius: 10px 0 0 0;
 }

 th:last-child {
  -moz-border-radius: 0 10px 0 0;
  -webkit-border-radius: 0 10px 0 0;
      border-radius: 0 10px 0 0;
 }

th {
	background-color: #5E9188;
	color: #FFF;
	cursor: pointer;
	padding: 5px 10px;
}

td a {
	color: #663300;
	display: block;
	padding: 5px 10px;
}

td, th { text-align: left; }
a { text-decoration: none; }
th a { padding-left: 0 }
td:first-of-type a { padding-left: 35px; }
th:first-of-type { padding-left: 35px; }
tr:nth-of-type(even) { background-color: #F3F3F3; }
tr:nth-of-type(odd) { background-color: #E6E6E6; }
tr:hover td { background-color:#CACACA; }
tr:last-child td:first-child { -moz-border-radius: 0 0 0 10px; -webkit-border-radius: 0 0 0 10px; border-radius: 0 0 0 10px; }
tr:last-child td:last-child { -moz-border-radius: 0 0 10px 0; -webkit-border-radius: 0 0 10px 0;border-radius: 0 0 10px 0; }
       
</style>
</head>

<body>
<!--Borrowed from Giovanni Petrucciani, Aug 2013-->
<form><input type="text" class="search rounded" name="match" value="<?php if (isset($_GET['match'])) print htmlspecialchars($_GET['match']);  ?>"  placeholder="Search..."></form> 
 <table>
   <thead>
     <tr>
          <th>Name</th>
          <th>Date Modified</th>
        </tr>
      </thead>
      <tbody>
      <?php
      date_default_timezone_set('America/New_York');

 $cleaned_items = array_diff(scandir('.'), array('.'), glob("*.pdf"));
 $png_files = glob("*.png");
 //have to do it this way because browsers can't display pdf files, but we need pdf links easily acccessible for download
 $non_image_items = array_diff($cleaned_items, $png_files);
 //list folders first
 usort ($non_image_items, create_function ('$a, $b', '
    return is_dir ($a)? (is_dir ($b) ? strnatcasecmp ($a, $b) : -1)
    : (is_dir ($b) ? 1 : (
        strcasecmp (pathinfo ($a, PATHINFO_EXTENSION), pathinfo ($b, PATHINFO_EXTENSION)) == 0
        ? strnatcasecmp ($a, $b)
        : strcasecmp (pathinfo ($a, PATHINFO_EXTENSION), pathinfo ($b, PATHINFO_EXTENSION))
    ));
 '));
  
  foreach ($non_image_items as $item) {
          if (isset($_GET['match']) && !fnmatch('*'.$_GET['match'].'*', $item) && count($png_files)==0) continue;
          $modtime=date("M j Y g:i A", filemtime($item));
          $timekey=date("YmdHis", filemtime($item));
          $name = $item;
          if(is_dir($item)) { $name="<b>".$item."/</b>"; $modtime=""; }
          print("
          <tr>
            <td><a href='./$item'>$name</a></td>
            <td sorttable_customkey='$timekey'><a href='./$item'>$modtime</a></td>
          </tr>");
        }

  ?>
     </tbody>
    </table> 

 <?php
 foreach ($png_files as $file) {
     if (isset($_GET['match']) && !fnmatch('*'.$_GET['match'].'*', $file)) continue;
     echo '<div class="photo-link smoothbox">';
     $parts=preg_split("[/\\.]", $file);
     $pdf_version = $parts[0].".pdf";     
     echo '<a href="',$pdf_version,'" rel="gallery"><img src="',$file,'" style="width: 300px;" /></a>';
     echo '</div>';
     

 }
 ?>
</body>

</html>
