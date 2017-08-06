object frmOptions: TfrmOptions
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Options'
  ClientHeight = 406
  ClientWidth = 567
  Color = clWindow
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  DesignSize = (
    567
    406)
  PixelsPerInch = 96
  TextHeight = 13
  object shpDialogBackground: TShape
    Left = 0
    Top = 0
    Width = 562
    Height = 58
    Anchors = [akLeft, akTop, akRight]
    Brush.Style = bsClear
    Pen.Color = clWhite
    ExplicitWidth = 556
  end
  object lblTitle: TLabel
    Left = 8
    Top = 5
    Width = 217
    Height = 16
    Align = alCustom
    AutoSize = False
    Caption = 'Options'
    Color = clWindow
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    WordWrap = True
  end
  object imgDialogPicture: TImage
    Left = 519
    Top = 0
    Width = 48
    Height = 406
    Align = alRight
    Anchors = [akTop, akRight]
    AutoSize = True
    Picture.Data = {
      07544269746D6170E8020000424DE8020000000000003E000000280000003000
      00003A0000000100040002000000AA020000120B0000120B0000020000000000
      0000C6C3C600FFFFFF00301100003011000030110000301100001A1100040001
      121100001A1105001111000019110008001000010F1100001911000800111001
      0F11000018110008001110011011000018110008001110011011000017110008
      0011100111110000171100080011100111110000161100080011100112110000
      0D1100100001111110011100131100000D110400041100080011100113110000
      0D110500000C111001110011121100000D110010001000100111001113110000
      0D1100100011000001110011131100000D110010001110001110011113110000
      0D11020009110200161100000D11020008110A000F1100000D11020009110A00
      0E1100000D1102000F11000400010E1100000D1102000E11000400010F110000
      0D1102000D1100040001101100000D1102000C1100040001111100000D110200
      0B1100040001121100000D1102000A1100040001131100000D11020009110004
      0001141100000D110200081100040001151100000D1102000711000400011611
      0000051102000611020006110004000117110000051100140001111100111110
      0011171100000611001000011110011110001A11000007110010000111001110
      0011191100000811000C0001100110001C1100000911000C0001001000111B11
      00000A110008001000001E1100000D1104001F11000002100900000811000110
      0900141100000210090007110A0014110000301100000A110008001111001E11
      00000911000C0001001000111B1100000811000C0001100110001C1100000711
      00100001110011100011191100000611001000011110011110001A1100000511
      0014000111110011111000111711000005110200061102000611020019110000
      0D110200211100000D110200211100000D110200211100000D11020021110000
      3011000030110000301100003011000030110001}
    Proportional = True
    Transparent = True
    ExplicitHeight = 58
  end
  object lblDescription: TLabel
    Left = 8
    Top = 25
    Width = 505
    Height = 31
    Align = alCustom
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    Caption = 'Configure the appearance and behaviour of FileOptimizer'
    Color = clWindow
    ParentColor = False
    ParentShowHint = False
    ShowHint = True
    WordWrap = True
    ExplicitWidth = 672
  end
  object shpDialogLineG1: TShape
    Left = 0
    Top = 56
    Width = 562
    Height = 2
    Anchors = [akLeft, akTop, akRight]
    Brush.Color = clGray
    Pen.Color = clGray
    ExplicitWidth = 556
  end
  object tabOptions: TPageControl
    Left = 0
    Top = 65
    Width = 567
    Height = 303
    ActivePage = pagGeneral1
    Align = alCustom
    HotTrack = True
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    object pagGeneral1: TTabSheet
      Caption = 'General &1'
      ParentShowHint = False
      ShowHint = True
      object lblOptimizationLevel: TLabel
        Left = 7
        Top = 22
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Optimization level'
        FocusControl = cboOptimizationLevel
        ParentShowHint = False
        ShowHint = False
      end
      object lblProcessPriority: TLabel
        Left = 7
        Top = 48
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Process priority'
        FocusControl = cboProcessPriority
        ParentShowHint = False
        ShowHint = False
      end
      object lblCheckForUpdates: TLabel
        Left = 7
        Top = 74
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Check for updates'
        FocusControl = cboCheckForUpdates
        ParentShowHint = False
        ShowHint = False
      end
      object lblLogLevel: TLabel
        Left = 7
        Top = 99
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Log level'
        FocusControl = cboLogLevel
        ParentShowHint = False
        ShowHint = False
      end
      object lblExcludeMask: TLabel
        Left = 7
        Top = 123
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Exclude mask'
        FocusControl = txtExcludeMask
        ParentShowHint = False
        ShowHint = False
      end
      object lblIncludeMask: TLabel
        Left = 7
        Top = 147
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Include mask'
        FocusControl = txtIncludeMask
        ParentShowHint = False
        ShowHint = False
      end
      object lblTempDirectory: TLabel
        Left = 7
        Top = 171
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Temp directory'
        FocusControl = txtTempDirectory
        ParentShowHint = False
        ShowHint = False
      end
      object chkKeepAttributes: TCheckBox
        Left = 7
        Top = 194
        Width = 281
        Height = 17
        Hint = 
          'Keep original readonly, system, hidden and archive attributes as' +
          ' well as creation and modification timestamps.'
        Caption = '&Keep file attributes'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object cboOptimizationLevel: TComboBox
        Left = 168
        Top = 19
        Width = 245
        Height = 21
        Hint = 'Optimization level from best speed to best compression.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        Items.Strings = (
          '0: Fastest'
          '1: Faster'
          '2: Fast'
          '3:'
          '4:'
          '5: Normal (Default)'
          '6:'
          '7: Good'
          '8: Better'
          '9: Best')
      end
      object cboProcessPriority: TComboBox
        Left = 168
        Top = 45
        Width = 245
        Height = 21
        Hint = 'Process priority from most conservative to best performance.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        Items.Strings = (
          'Idle'
          'Below normal'
          'Normal (Default)'
          'Above normal'
          'High'
          'Realtime')
      end
      object cboCheckForUpdates: TComboBox
        Left = 168
        Top = 71
        Width = 245
        Height = 21
        Hint = 'Automatically check for program updates.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        Items.Strings = (
          'Ask'
          'Automatically (Default)'
          'Never')
      end
      object cboLogLevel: TComboBox
        Left = 168
        Top = 97
        Width = 245
        Height = 21
        Hint = 'Debugging level to output on program log.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
        Items.Strings = (
          '0: None (Default)'
          '1: Critical'
          '2: Error'
          '3: Warning'
          '4: Information')
      end
      object chkDoNotUseRecycleBin: TCheckBox
        Left = 7
        Top = 213
        Width = 281
        Height = 17
        Hint = 
          'When checked original files will not be backed up in the system ' +
          'trashcan.'
        Caption = '&Do not use recycle bin'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 6
      end
      object txtExcludeMask: TEdit
        Left = 168
        Top = 123
        Width = 245
        Height = 21
        Hint = 
          'Files containing this mask (substring) on name or path will be e' +
          'xcluded from optimization. You can use semicolon (;) to specify ' +
          'more than one substring being excluded.'
        AutoSize = False
        HideSelection = False
        MaxLength = 127
        ParentShowHint = False
        ShowHint = True
        TabOrder = 5
      end
      object txtIncludeMask: TEdit
        Left = 168
        Top = 147
        Width = 245
        Height = 21
        Hint = 
          'If not empty, only files containing this mask (substring) on nam' +
          'e or path will be included from optimization. You can use semico' +
          'lon to specify more than one substring being included.'
        AutoSize = False
        HideSelection = False
        MaxLength = 127
        ParentShowHint = False
        ShowHint = True
        TabOrder = 7
      end
      object chkAllowMultipleInstances: TCheckBox
        Left = 7
        Top = 232
        Width = 281
        Height = 17
        Hint = 
          'Allow having more than one FileOptimizer instance. If not, a war' +
          'ning will appear.'
        Caption = '&Allow multiple instances'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 8
      end
      object txtTempDirectory: TEdit
        Left = 168
        Top = 171
        Width = 245
        Height = 21
        Hint = 
          'If not empty specified directory will be used for temporary stor' +
          'age instead of system'#39's %TEMP%.'
        AutoSize = False
        HideSelection = False
        MaxLength = 127
        ParentShowHint = False
        ShowHint = True
        TabOrder = 9
      end
    end
    object pagGeneral2: TTabSheet
      Caption = 'General &2'
      ImageIndex = 21
      object lblDisablePluginMask: TLabel
        Left = 7
        Top = 22
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Disable plugin mask'
        FocusControl = txtDisablePluginMask
        ParentShowHint = False
        ShowHint = False
      end
      object lblLeanifyIterations: TLabel
        Left = 7
        Top = 45
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Leanify iterations'
        FocusControl = spnLeanifyIterations
        ParentShowHint = False
        ShowHint = False
      end
      object txtDisablePluginMask: TEdit
        Left = 168
        Top = 17
        Width = 245
        Height = 21
        Hint = 
          'Allow excluding execution of certain plugins. It is case insensi' +
          'tive, and allows more than one item to be specified by using sem' +
          'icolon as separator.'
        AutoSize = False
        HideSelection = False
        MaxLength = 127
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object chkBeepWhenDone: TCheckBox
        Left = 7
        Top = 70
        Width = 281
        Height = 17
        Hint = 'Beep the speaker when optimization completes.'
        Caption = '&Beep when done'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
      object chkShutdownWhenDone: TCheckBox
        Left = 7
        Top = 87
        Width = 281
        Height = 17
        Hint = 'Shutdown computer when optimization completes.'
        Caption = '&Shutdown when done'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
      end
      object chkClearWhenComplete: TCheckBox
        Left = 7
        Top = 103
        Width = 281
        Height = 17
        Hint = 'Automatically clear file list when optimization is completed.'
        Caption = '&Clear when complete'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
      end
      object chkAllowDuplicates: TCheckBox
        Left = 7
        Top = 121
        Width = 281
        Height = 17
        Hint = 
          'Allow adding same file more than once. If enabled, adding to the' +
          ' grid will be much faster, specially on very large grids.'
        Caption = '&Allow duplicates'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
      end
      object spnLeanifyIterations: TSpinEdit
        Left = 168
        Top = 45
        Width = 50
        Height = 22
        Hint = 
          'If specified, number of trial iterations in all Leanify executio' +
          'ns will use this vaule. If not, iterations are calculated depend' +
          'ing on the Optimization level.'
        Increment = 50
        MaxValue = 1000
        MinValue = -1
        ParentShowHint = False
        ShowHint = True
        TabOrder = 5
        Value = 50
      end
      object chkEnableCache: TCheckBox
        Left = 7
        Top = 138
        Width = 281
        Height = 17
        Hint = 
          'Enable cache of already optimized files to automatically skip th' +
          'em.'
        Caption = '&Enable cache'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 6
      end
    end
    object pagAppearance: TTabSheet
      Caption = '&Appearance'
      ImageIndex = 13
      object lblTheme: TLabel
        Left = 7
        Top = 22
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Theme'
        FocusControl = cboTheme
        ParentShowHint = False
        ShowHint = False
      end
      object lblDonator: TLabel
        Left = 7
        Top = 69
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Donator'
        FocusControl = txtDonator
        ParentShowHint = False
        ShowHint = False
      end
      object lblFilenameFormat: TLabel
        Left = 7
        Top = 44
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Filename format'
        FocusControl = cboFilenameFormat
        ParentShowHint = False
        ShowHint = False
      end
      object cboTheme: TComboBox
        Left = 168
        Top = 19
        Width = 245
        Height = 21
        Hint = 'Visual theme.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Items.Strings = (
          'Windows (Default)'
          'Metropolis UI Black'
          'Luna'
          'Windows 10')
      end
      object txtDonator: TEdit
        Left = 168
        Top = 69
        Width = 245
        Height = 21
        Hint = 
          'If you have already donated to support FileOptimizer development' +
          ', enter here the email address or name you used'
        AutoSize = False
        HideSelection = False
        MaxLength = 127
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
      object chkShowToolBar: TCheckBox
        Left = 7
        Top = 93
        Width = 281
        Height = 17
        Hint = 'Show icons toolbar on main window'
        Caption = '&Show toolbar'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
      end
      object chkAlwaysOnTop: TCheckBox
        Left = 7
        Top = 112
        Width = 281
        Height = 17
        Hint = 'Show main window always on top.'
        Caption = '&Always on top'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
      end
      object cboFilenameFormat: TComboBox
        Left = 168
        Top = 44
        Width = 245
        Height = 21
        Hint = 'Specify the format to display filenames in the list.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
        OnChange = cboPDFProfileChange
        Items.Strings = (
          'Full path and Filename (Default)'
          'Filename only'
          'Drive letter + Partial path + Filename'
          'Drive letter + Partial (path + Filename)')
      end
    end
    object pagBMP: TTabSheet
      Caption = '&BMP'
      ImageIndex = 15
      object chkBMPCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagCSS: TTabSheet
      Caption = '&CSS'
      ImageIndex = 6
      object lblCSSTemplate: TLabel
        Left = 7
        Top = 46
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Template'
        FocusControl = cboCSSTemplate
        ParentShowHint = False
        ShowHint = False
      end
      object chkCSSEnableTidy: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Enable tidy. Results in smaller files, but can happen they are n' +
          'ot editable anymore.'
        Caption = '&Enable Tidy'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = chkCSSEnableTidyClick
      end
      object cboCSSTemplate: TComboBox
        Left = 168
        Top = 46
        Width = 245
        Height = 21
        Hint = 
          'Compression template, from safer and worse compression, to highe' +
          'st compression'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        Items.Strings = (
          'Low (Default)'
          'High'
          'Highest')
      end
    end
    object pagEXE: TTabSheet
      Caption = '&EXE'
      ImageIndex = 6
      object chkEXEDisablePETrim: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Disable PETrim. When enabled, PETrim will not be used, resulting' +
          ' in less EXE corruption at the cost of larger file size.'
        Caption = '&Disable PETrim'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object chkEXEEnableUPX: TCheckBox
        Left = 7
        Top = 43
        Width = 281
        Height = 17
        Hint = 
          'Allow excluding execution of certain plugins. It is case insensi' +
          'tive, and allows more than one item to be specified by using sem' +
          'icolon as separator.'
        Caption = '&Enable UPX'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
    end
    object pagGIF: TTabSheet
      Caption = '&GIF'
      ImageIndex = 6
      object chkGIFCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object chkGIFAllowLossy: TCheckBox
        Left = 7
        Top = 41
        Width = 281
        Height = 17
        Hint = 
          'Allowing lossy optimizations will get higher files reduction at ' +
          'the cost of some quality loss, even if visually unnoticeable or ' +
          'not'
        Caption = '&Allow lossy optimizations'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
    end
    object pagGZ: TTabSheet
      Caption = '&GZ'
      ImageIndex = 6
      object chkGZCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagHTML: TTabSheet
      Caption = '&HTML'
      ImageIndex = 6
      object chkHTMLEnableTidy: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Enable Tidy. Results in smaller files, but can happen they are n' +
          'ot editable anymore. Note that this applies to both SVG and HTML' +
          ' file types'
        Caption = '&Enable Tidy'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagJPEG: TTabSheet
      Caption = '&JPEG'
      ImageIndex = 5
      object chkJPEGCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object chkJPEGUseArithmeticEncoding: TCheckBox
        Left = 7
        Top = 41
        Width = 281
        Height = 17
        Hint = 
          'Arithmetic encoding gives additional saving reductions, but is i' +
          'ncompatible with most programs.'
        Caption = '&Use arithmetic encoding'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
      object chkJPEGAllowLossy: TCheckBox
        Left = 7
        Top = 60
        Width = 281
        Height = 17
        Hint = 
          'Allowing lossy optimizations will get higher files reduction at ' +
          'the cost of some quality loss, even if visually unnoticeable or ' +
          'not'
        Caption = '&Allow lossy optimizations'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
      end
    end
    object pagJS: TTabSheet
      Caption = '&JS'
      ImageIndex = 6
      object lblJSAdditionalExtensions: TLabel
        Left = 7
        Top = 46
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Additional Extensions'
        FocusControl = txtJSAdditionalExtensions
        ParentShowHint = False
        ShowHint = False
      end
      object chkJSEnableJSMin: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Enable jsmin. Results in smaller files, but can happen they are ' +
          'not editable anymore.'
        Caption = '&Enable JSMin'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object txtJSAdditionalExtensions: TEdit
        Left = 168
        Top = 46
        Width = 245
        Height = 21
        Hint = 'Add extra extensions to be threated as JS/JSON.'
        AutoSize = False
        HideSelection = False
        MaxLength = 127
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
    end
    object pagLUA: TTabSheet
      Caption = '&LUA'
      ImageIndex = 12
      object chkLUAEnableLeanify: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Enable Leanify. Results in smaller files, but can happen they ar' +
          'e not editable anymore.'
        Caption = '&Enable Leanify'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagMisc: TTabSheet
      Caption = '&Miscelaneous'
      ImageIndex = 8
      object chkMiscCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagMP3: TTabSheet
      Caption = '&MP3'
      ImageIndex = 8
      object chkMP3CopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagMP4: TTabSheet
      Caption = '&MP4'
      ImageIndex = 8
      object chkMP4CopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagPCX: TTabSheet
      Caption = '&PCX'
      ImageIndex = 8
      object chkPCXCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagPDF: TTabSheet
      Caption = '&PDF'
      ImageIndex = 7
      object lblPDFProfile: TLabel
        Left = 7
        Top = 22
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Profile'
        FocusControl = cboPDFProfile
        ParentShowHint = False
        ShowHint = False
      end
      object lblPDFCustomDPI: TLabel
        Left = 7
        Top = 49
        Width = 155
        Height = 13
        AutoSize = False
        Caption = '&Custom DPI'
        FocusControl = spnPDFCustomDPI
        ParentShowHint = False
        ShowHint = False
      end
      object cboPDFProfile: TComboBox
        Left = 168
        Top = 22
        Width = 245
        Height = 21
        Hint = 'Compression profile, from less size, to best quality.'
        Style = csDropDownList
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnChange = cboPDFProfileChange
        Items.Strings = (
          'None: No downsampling (Default)'
          'Screen: 72 dpi'
          'Ebook: 150 dpi'
          'Printer: 300 dpi'
          'Prepress: 300 dpi and color preserve'
          'Custom')
      end
      object spnPDFCustomDPI: TSpinEdit
        Left = 168
        Top = 49
        Width = 50
        Height = 22
        Hint = 
          'When custom profile is choosen, it allows you to specify a custo' +
          'm DPI for downsampling images'
        Increment = 50
        MaxValue = 3000
        MinValue = 50
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        Value = 50
      end
      object chkPDFSkipLayered: TCheckBox
        Left = 4
        Top = 73
        Width = 281
        Height = 17
        Hint = 
          'Skip processing of PDF files containing layered objects. Results' +
          ' in more compatible files with higher size.'
        Caption = '&Skip layered'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
      end
    end
    object pagPNG: TTabSheet
      Caption = '&PNG'
      ImageIndex = 10
      object chkPNGCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object chkPNGAllowLossy: TCheckBox
        Left = 7
        Top = 41
        Width = 281
        Height = 17
        Hint = 
          'Allowing lossy optimizations will get higher files reduction at ' +
          'the cost of some quality loss, even if visually unnoticeable or ' +
          'not'
        Caption = '&Allow lossy optimizations'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
    end
    object pagTGA: TTabSheet
      Caption = '&TGA'
      ImageIndex = 8
      object chkTGACopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagTIFF: TTabSheet
      Caption = '&TIFF'
      ImageIndex = 8
      object chkTIFFCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagXML: TTabSheet
      Caption = '&XML'
      ImageIndex = 11
      object chkXMLEnableLeanify: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 
          'Enable Leanify. Results in smaller files, but can happen they ar' +
          'e not editable anymore.'
        Caption = '&Enable Leanify'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
    end
    object pagZIP: TTabSheet
      Caption = '&ZIP'
      ImageIndex = 9
      object chkZIPCopyMetadata: TCheckBox
        Left = 7
        Top = 22
        Width = 281
        Height = 17
        Hint = 'Copy file metadata. Else strip all unneded information.'
        Caption = '&Copy metadata'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object chkZIPRecurse: TCheckBox
        Left = 7
        Top = 41
        Width = 281
        Height = 17
        Hint = 'Enable optimization inside archives (recursive optimization).'
        Caption = '&Recurse'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
    end
  end
  object butRestoreDefaults: TButton
    Left = 8
    Top = 374
    Width = 95
    Height = 25
    Hint = 'Restore all options to its factory settings values.'
    Caption = '&Restore defaults'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    OnClick = butRestoreDefaultsClick
  end
  object butOK: TButton
    Left = 400
    Top = 374
    Width = 75
    Height = 25
    Hint = 'Accept and apply all changes made to options.'
    Caption = '&OK'
    Default = True
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = butOKClick
  end
  object butCancel: TButton
    Left = 481
    Top = 374
    Width = 75
    Height = 25
    Hint = 'Discard any changes made to options.'
    Cancel = True
    Caption = '&Cancel'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = butCancelClick
  end
end
