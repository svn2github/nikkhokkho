<?php
	@error_reporting(E_ALL);
	@ini_set('display_errors', '1');

	$aColumns = Array
	(
		'Date/Time' => @date('Y-m-d H:i:s'),
		'IP' => @$_SERVER['HTTP_X_REMOTE_ADDR'],
		'UserAgent' => @$_SERVER['HTTP_USER_AGENT'],
	    'Left' => 0,
	    'Top' => 0,
	    'Width' => 0,
	    'Height' => 0,
	    'WindowState' => 0,
	    'DefaultMonitor' => 0,
	    'RibbonMinimized' => false,
	    'Col0Width' => 0,
	    'Col1Width' => 0,
	    'Col2Width' => 0,
	    'Col3Width' => 0,
	    'Col4Width' => 0,
	    'BMPCopyMetadata' => false,
	    'CSSEnableTidy' => false,
	    'CSSTemplate' => '',
	    'EXEDisablePETrim' => false,
	    'EXEEnableUPX' => false,
	    'GIFCopyMetadata' => false,
	    'GIFAllowLossy' => false,
	    'GZCopyMetadata' => false,
	    'HTMLEnableTidy' => false,
	    'JPEGCopyMetadata' => false,
	    'JPEGUseArithmeticEncoding' => false,
	    'JPEGAllowLossy' => false,
	    'JSEnableJSMin' => false,
	    'LUAEnableLeanify' => false,
	    'MiscCopyMetadata' => false,
	    'MP3CopyMetadata' => false,
	    'PCXCopyMetadata' => false,
	    'PDFProfile' => '',
	    'PDFCustomDPI' => 0,
	    'PNGCopyMetadata' => false,
	    'PNGAllowLossy' => false,
	    'TIFFCopyMetadata' => false,
	    'XMLEnableLeanify' => false,
	    'ZIPCopyMetadata' => false,
	    'ZIPRecurse' => false,
	    'KeepAttributes' => false,
	    'DoNotUseRecycleBin' => false,
	    'ExcludeMask' => '',
	    'DisablePluginMask' => '',
	    'BeepWhenDone' => false,
	    'ShutdownWhenDone' => false,
	    'AlwaysOnTop' => false,
	    'AllowDuplicates' => false,
	    'Level' => 0,
	    'ProcessPriority' => 0,
	    'CheckForUpdates' => 0,
	    'LogLevel' => 0,
	    'FilenameFormat' => 0,
	    'LeanifyIterations' => 0,
	    'Theme' => '',
	    'UseRibbon' => false,
	    'TempDirectory' => '',
	    'Version' => '9.20.1585',
	    'Time' => 0,
	    'Opens' => 0,
	    'Files' => 0,
	    'TotalBytes' => 0,
	    'SavedBytes' => 0,
	    'Session' => ''
	);
	
	echo $aColumns['Version'];
	
	$sIni = @$_GET['ini'];
	//$sIni = "[frmMain]\r\nLeft=260\r\nTop=260\r\nWidth=1440\r\nHeight=789\r\nWindowState=0\r\nDefaultMonitor=3\r\nRibbonMinimized=false\r\nCol0Width=512\r\nCol1Width=512\r\nCol2Width=512\r\nCol3Width=512\r\nCol4Width=512\r\n[Options]\r\nBMPCopyMetadata=false\r\nCSSEnableTidy=false\r\nCSSTemplate=\r\nEXEDisablePETrim=false\r\nEXEEnableUPX=false\r\nGIFCopyMetadata=false\r\nGIFAllowLossy=false\r\nGZCopyMetadata=false\r\nHTMLEnableTidy=false\r\nJPEGCopyMetadata=false\r\nJPEGUseArithmeticEncoding=false\r\nJPEGAllowLossy=false\r\nJSEnableJSMin=false\r\nLUAEnableLeanify=false\r\nMiscCopyMetadata=false\r\nMP3CopyMetadata=false\r\nPCXCopyMetadata=false\r\nPDFProfile=\r\nPDFCustomDPI=0\r\nPNGCopyMetadata=false\r\nPNGAllowLossy=false\r\nTIFFCopyMetadata=false\r\nXMLEnableLeanify=false\r\nZIPCopyMetadata=false\r\nZIPRecurse=false\r\nKeepAttributes=false\r\nDoNotUseRecycleBin=false\r\nExcludeMask=\r\nDisablePluginMask=\r\nBeepWhenDone=false\r\nShutdownWhenDone=false\r\nAlwaysOnTop=false\r\nAllowDuplicates=false\r\nLevel=0\r\nProcessPriority=0\r\nCheckForUpdates=0\r\nLogLevel=0\r\nFilenameFormat=0\r\nLeanifyIterations=0\r\nTheme=\r\nTempDirectory=\r\nVersion=\r\n[Statistics]\r\nTime=9066\r\nOpens=0\r\nFiles=0\r\nTotalBytes=0\r\nSavedBytes=0\r\n";
	if (!empty($sIni))
	{
		$aIni = @parse_ini_string($sIni, false, INI_SCANNER_RAW);
		
		if (!file_exists('FileOptimizerVersion.csv'))
		{
			$iFile = fopen('FileOptimizerVersion.csv', 'a');
	    	fputcsv($iFile, array_keys($aColumns), ';');
	    	fclose($iFile);
		}
		
		$aColumns = @array_merge($aColumns, $aIni);
		$iFile = fopen('FileOptimizerVersion.csv', 'a');
	    fputcsv($iFile, array_values($aColumns), ';');
	    fclose($iFile);
	}

?>