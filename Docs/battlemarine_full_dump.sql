-- MySQL dump 10.13  Distrib 5.6.28, for Linux (x86_64)
--
-- Host: mocha    Database: battlemarine
-- ------------------------------------------------------
-- Server version	5.6.28-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `account` (
  `ac_aid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `ac_loginid` char(32) NOT NULL,
  `ac_passwd` char(64) NOT NULL,
  `ac_name` char(32) NOT NULL DEFAULT 'NONAME',
  `ac_point` int(10) NOT NULL DEFAULT '10000',
  `ac_grade` enum('PLAYER','SU') NOT NULL DEFAULT 'PLAYER',
  `ac_login_time` int(10) unsigned NOT NULL DEFAULT '0',
  `ac_logout_time` int(10) unsigned NOT NULL DEFAULT '0',
  `ac_create_time` int(10) unsigned NOT NULL DEFAULT '0',
  `ac_time` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`ac_aid`),
  UNIQUE KEY `ac_loginid_UNIQUE` (`ac_loginid`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,'foxip','*3D3B92F242033365AE5BC6A8E6FC3E1679F4140A','테스트',10000,'PLAYER',0,0,0,'2017-01-18 14:22:08');
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dropinfo`
--

DROP TABLE IF EXISTS `dropinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dropinfo` (
  `di_id` int(10) NOT NULL,
  `di_mod` enum('FFA','TDM','ZOMBIE') NOT NULL DEFAULT 'FFA',
  `di_type` enum('FIELD','RESPAWN') NOT NULL DEFAULT 'FIELD',
  `di_team` enum('NONE','RED','BLUE','GREEN') NOT NULL DEFAULT 'NONE',
  `di_item_id` int(11) NOT NULL DEFAULT '0',
  `di_map_id` int(11) NOT NULL,
  `di_x` float NOT NULL,
  `di_y` float NOT NULL,
  `di_prob` int(11) NOT NULL DEFAULT '0',
  `di_group` int(11) NOT NULL DEFAULT '0',
  `di_removal_time` int(11) NOT NULL DEFAULT '600',
  `di_respawn_time` int(11) NOT NULL DEFAULT '0',
  `di_left_over_time` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dropinfo`
--

LOCK TABLES `dropinfo` WRITE;
/*!40000 ALTER TABLE `dropinfo` DISABLE KEYS */;
INSERT INTO `dropinfo` VALUES (1,'FFA','FIELD','NONE',20000,0,0,0,3000,0,1000,500,0),(2,'FFA','FIELD','NONE',20010,0,0,0,5000,0,1000,700,0),(3,'FFA','FIELD','NONE',20020,0,0,0,500,0,1000,800,0),(4,'FFA','FIELD','NONE',20030,0,0,0,300,0,1000,1000,0),(5,'FFA','FIELD','NONE',20040,0,0,0,200,0,1000,500,0),(6,'TDM','FIELD','NONE',20050,0,0,0,7000,0,500,1000,0),(7,'TDM','FIELD','NONE',20060,0,0,0,3000,0,500,2000,0),(8,'TDM','FIELD','NONE',20000,0,0,0,3000,1,500,500,0),(9,'TDM','FIELD','NONE',20100,0,0,0,1000,1,500,1000,0),(10,'TDM','FIELD','NONE',20110,0,0,0,500,1,500,2000,0),(11,'TDM','FIELD','NONE',20120,0,0,0,500,1,500,2000,0),(12,'TDM','FIELD','NONE',20000,0,0,0,2000,2,500,1000,0),(13,'TDM','FIELD','NONE',20100,0,0,0,1000,2,500,2000,0),(14,'TDM','RESPAWN','BLUE',20000,0,150,150,3000,0,200,100,0),(15,'TDM','RESPAWN','GREEN',20010,0,200,200,3000,0,100,100,0);
/*!40000 ALTER TABLE `dropinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `inventory`
--

DROP TABLE IF EXISTS `inventory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `inventory` (
  `in_aid` int(10) unsigned NOT NULL,
  `in_offset` enum('INVENTORY','NONE') NOT NULL DEFAULT 'INVENTORY',
  `in_itemid` int(10) unsigned NOT NULL DEFAULT '0',
  `in_serial` bigint(20) unsigned NOT NULL DEFAULT '0',
  `in_count` int(11) NOT NULL DEFAULT '0',
  UNIQUE KEY `in_aid_UNIQUE` (`in_aid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `inventory`
--

LOCK TABLES `inventory` WRITE;
/*!40000 ALTER TABLE `inventory` DISABLE KEYS */;
/*!40000 ALTER TABLE `inventory` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `iteminfo`
--

DROP TABLE IF EXISTS `iteminfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `iteminfo` (
  `ii_id` int(10) unsigned NOT NULL DEFAULT '0',
  `ii_name` varchar(50) NOT NULL,
  `ii_type` enum('POINT','PASSIVE','ACTIVE','NONE') NOT NULL DEFAULT 'NONE',
  `ii_usable` set('FALSE','TRUE') NOT NULL DEFAULT 'FALSE',
  `ii_stocks` int(10) unsigned NOT NULL,
  `ii_buy_point` int(10) unsigned NOT NULL DEFAULT '0',
  `ii_sell_point` int(10) unsigned NOT NULL DEFAULT '0',
  `ii_desc` varchar(200) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `iteminfo`
--

LOCK TABLES `iteminfo` WRITE;
/*!40000 ALTER TABLE `iteminfo` DISABLE KEYS */;
INSERT INTO `iteminfo` VALUES (20000,'money','POINT','TRUE',10,10,20,'20000번 돈입니다'),(20010,'ammo','ACTIVE','TRUE',30,100,200,'20010번 총알입니다'),(20020,'ammo','ACTIVE','TRUE',50,100,150,'20020번 총알입니다'),(20030,'ammo','PASSIVE','TRUE',70,50,100,'20030번 총알입니다'),(20040,'money','POINT','TRUE',30,50,80,'20040번 돈입니다'),(20050,'ammo','PASSIVE','TRUE',100,30,80,'20050번 총알입니다'),(20060,'money','POINT','TRUE',50,100,100,'20060번 돈입니다'),(20100,'ammo','PASSIVE','TRUE',120,70,100,'20100번 총알입니다'),(20110,'ammo','ACTIVE','TRUE',150,80,100,'20110번 총알입니다'),(20120,'ammo','ACTIVE','TRUE',200,90,100,'20120번 총알입니다');
/*!40000 ALTER TABLE `iteminfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mapinfo`
--

DROP TABLE IF EXISTS `mapinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `mapinfo` (
  `mi_id` int(11) NOT NULL,
  `mi_name` varchar(30) NOT NULL,
  `mi_max_user` int(11) NOT NULL DEFAULT '16',
  `mi_mod_ffa` set('FALSE','TRUE') NOT NULL DEFAULT 'FALSE',
  `mi_mod_tdm` set('FALSE','TRUE') NOT NULL DEFAULT 'FALSE',
  `mi_mod_zombie` set('FALSE','TRUE') NOT NULL DEFAULT 'FALSE',
  `mi_desc` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `mapinfo`
--

LOCK TABLES `mapinfo` WRITE;
/*!40000 ALTER TABLE `mapinfo` DISABLE KEYS */;
INSERT INTO `mapinfo` VALUES (1,'theHunter',16,'TRUE','TRUE','TRUE','더 헌터'),(2,'LostTemple',8,'TRUE','TRUE','TRUE','로스트 템플'),(3,'FastInfinite',16,'FALSE','FALSE','TRUE','빠른 무한');
/*!40000 ALTER TABLE `mapinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `modinfo`
--

DROP TABLE IF EXISTS `modinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `modinfo` (
  `mi_mod` enum('FFA','TDM','ZOMBIE') NOT NULL DEFAULT 'FFA',
  `mi_map` int(11) NOT NULL DEFAULT '1',
  `mi_rule` int(11) NOT NULL DEFAULT '100',
  `mi_time` int(11) NOT NULL DEFAULT '0',
  `mi_itemdrop` set('FALSE','TRUE') NOT NULL DEFAULT 'TRUE'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `modinfo`
--

LOCK TABLES `modinfo` WRITE;
/*!40000 ALTER TABLE `modinfo` DISABLE KEYS */;
INSERT INTO `modinfo` VALUES ('FFA',1,50,0,'TRUE'),('TDM',1,1,300,'TRUE'),('ZOMBIE',1,1,0,'FALSE');
/*!40000 ALTER TABLE `modinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rewardinfo`
--

DROP TABLE IF EXISTS `rewardinfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `rewardinfo` (
  `ri_id` int(10) unsigned NOT NULL DEFAULT '0',
  `ri_type` enum('NORMAL','RARE','NONE') DEFAULT 'NONE',
  `ri_group` int(10) unsigned NOT NULL DEFAULT '0',
  `ri_prob` int(10) unsigned NOT NULL DEFAULT '0',
  `ri_item_id` int(10) unsigned NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `rewardinfo`
--

LOCK TABLES `rewardinfo` WRITE;
/*!40000 ALTER TABLE `rewardinfo` DISABLE KEYS */;
INSERT INTO `rewardinfo` VALUES (100010,'RARE',1,1000,20100),(100020,'RARE',1,1000,20060),(100010,'NORMAL',2,2000,20010),(100020,'NORMAL',2,2000,20020),(100030,'NORMAL',2,2000,20030),(100010,'RARE',3,500,20120),(100020,'NORMAL',3,2500,20020);
/*!40000 ALTER TABLE `rewardinfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'battlemarine'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-02-04 13:26:25
