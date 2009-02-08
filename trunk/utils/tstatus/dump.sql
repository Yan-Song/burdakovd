CREATE TABLE IF NOT EXISTS `cache` (
  `url` varchar(120) NOT NULL,
  `time` bigint(20) NOT NULL,
  `data` text NOT NULL,
  PRIMARY KEY  (`url`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/* дамп нужен только для myslq,
в sqlite таблица будет создана скриптом, вручную создавать не нужно */