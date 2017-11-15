<?php
	$sSearch = @filter_var($_GET['q'], FILTER_SANITIZE_STRING);


	function GetBanner()	
	{
		$iRnd = rand(0, 100);
		if ($iRnd < 5)
		{
			//Adsense 468x60
			//$sBanner = '<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script><ins class="adsbygoogle" style="display:inline-block;width:468px;height:60px" data-ad-client="ca-pub-6958213404940013" data-ad-slot="7375140027"></ins><script>(adsbygoogle = window.adsbygoogle || []).push({});</script>';
			//Adsense adaptable
			$sBanner = '<script async src="//pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script><ins class="adsbygoogle" style="display:block" data-ad-client="ca-pub-6958213404940013" data-ad-slot="8676613408" data-ad-format="auto"></ins><script>(adsbygoogle = window.adsbygoogle || []).push({});</script>';
		}
		else if ($iRnd < 100)
		{
			//Chitika 320x50
			$sBanner = '<script type="text/javascript">( function() { if (window.CHITIKA === undefined) { window.CHITIKA = { \'units\' : [] }; }; var unit = {"calltype":"async[2]","publisher":"guti","width":320,"height":50,"sid":"Chitika Default"}; var placement_id = window.CHITIKA.units.length; window.CHITIKA.units.push(unit); document.write(\'<div id="chitikaAdBlock-\' + placement_id + \'"></div>\');}());</script><script type="text/javascript" src="//cdn.chitika.net/getads.js" async></script>';
		}
		return($sBanner);
	}
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>Search: <?php echo @substr($sSearch, 0, 80); ?></title> 
	<meta http-equiv="refresh" content="<?php echo rand(5, 35); ?>"/>
	<style type="text/css">
		html, body
		{
			overflow: hidden;
		}
	</style>	
</head>
	
<body leftmargin=0 topmargin=0 rightmargin=0 bottommargin=0 marginwidth=0 marginheight=0 scroll="no">

<script language="Javascript" type="text/javascript">
	document.addEventListener("contextmenu", function(evtEvent)
	{
    	evtEvent.preventDefault();
	}, false);
</script>

<table border=0 cellspacing=0 cellpadding=0 width="100% height="100%" align="left">
	<tr>
		<td valign="top"><?php echo GetBanner(); ?></td>
		<td valign="top"><?php echo GetBanner(); ?></td>
		<td valign="top"><?php echo GetBanner(); ?></td>
		<td valign="top"><?php echo GetBanner(); ?></td>
		<td valign="top"><?php echo GetBanner(); ?></td>
	</tr>
	<tr>
		<td colspan=5><br><br><br><br><br><br><br>
			<?php echo $sSearch; ?></td>
	</tr>
</table>
</body>
</html>
