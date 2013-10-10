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
      width: 88.3%;
      margin: 0 auto;
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

    .pic {
      width: 300px;
    }

    .photo-link { text-align: center;
       padding: 5px;
       border-radius: 0.5em;
       margin: 5px 0;
       border: 1px solid #ccc;
       display: block;
       float: left;
       background: white
    }

    table {
      border-collapse: collapse;
      border-spacing: 0;
      width: 100%;
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
       
    slider: {
      color: white;
      width: 80%;
    }
    ui-slider: {
      width: 600px;
      clear: right;
    }
  </style>
  <link rel="stylesheet" href="http://code.jquery.com/ui/1.10.3/themes/smoothness/jquery-ui.css"/>
  <script src="http://code.jquery.com/jquery-1.9.1.js"></script>
  <!-- <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script> -->
  <script src="http://code.jquery.com/ui/1.10.3/jquery-ui.js"></script>
  <script>
    function fix_margins() {
      var width = parseFloat($(".pic").css('width'));
      $(".pic").css("margin-left", "0px");
      var picwidth = width + 10;
      var bodywidth = parseFloat($("body").css("width"));
      var npics = Math.floor(bodywidth / picwidth);
      var gap = Math.floor((bodywidth - npics * picwidth) / (npics - 1)) - 3;
      var count = 0;
      $(".photo-link").each(function(idx) {
        if ($(this).css("display") == "none") {
        } else {
          count += 1;
          if ((count % npics) != 1) {
            $(this).css("margin-left", gap + "px");
            // $("#debug").text($("#debug").text() + "\n\n\n" + idx + " -> " + gap);
          }
        }
        $("#debug").text(npics + " * " + picwidth + " -> " + gap + "; " + npics * width + " < " + bodywidth);
      });
    }

    $(document).ready(function() {
      fix_margins();

      $("#slider-size").slider({
        min: 100,
        max: 400,
        values: [300],
        slide: function(event, ui) {
          $(".pic").css("width", ui.values[0] + "px");
          fix_margins();
        }
      });

      // Could also be
      // $("#form_id).submit(function...
      $("#search").keyup(function() {
        var reg = new RegExp($(this).val(), 'i');
        $(".photo-link").each(function(idx) {
          if (reg.test($(this).attr('id'))) {
            $(this).fadeIn(1000, fix_margins);
          } else {
            $(this).fadeOut(1000, fix_margins);
          }
        });
      });
    });
  </script>
</head>

<body>
<!--Borrowed from Giovanni Petrucciani, Aug 2013-->
  <form>
    <input
      id="search"
      type="text"
      class="search rounded"
      name="match"
      value="<?php if (isset($_GET['match'])) print htmlspecialchars($_GET['match']);  ?>"
      placeholder="Search...">
    </input>
  </form>
  <div id="slider-size"></div>
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
     if (isset($_GET['match']) && !fnmatch('*'.$_GET['match'].'*', $file, FNM_CASEFOLD)) continue;
     echo '<div class="pic photo-link smoothbox" id="' . $file . '">';
     $parts=preg_split("[/\\.]", $file);
     $pdf_version = $parts[0].".pdf";     
     echo '<a href="',$pdf_version,'" rel="gallery"><img src="',$file,'" class="pic"/></a>';
     echo '</div>';
     

 }
 ?>
</body>

</html>
