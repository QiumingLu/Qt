/*
Navicat MySQL Data Transfer

Source Server         : test
Source Server Version : 50528
Source Host           : localhost:3306
Source Database       : library

Target Server Type    : MYSQL
Target Server Version : 50528
File Encoding         : 65001

Date: 2014-12-31 16:49:56
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `books`
-- ----------------------------
DROP TABLE IF EXISTS `books`;
CREATE TABLE `books` (
  `BOOK_ID` int(11) NOT NULL AUTO_INCREMENT,
  `BOOK_NAME` varchar(255) NOT NULL,
  `AUTHOR` varchar(255) NOT NULL,
  `PUBLISHING` varchar(255) NOT NULL,
  `CATEGORY_ID` int(11) NOT NULL,
  `PRICE` varchar(255) DEFAULT NULL,
  `DATE_IN` date NOT NULL,
  `QUANTITY_IN` int(11) DEFAULT NULL,
  `QUANTITY_OUT` int(11) DEFAULT NULL,
  `QUANTITY` int(11) DEFAULT NULL,
  PRIMARY KEY (`BOOK_ID`),
  KEY `CATEGORY_ID` (`CATEGORY_ID`),
  CONSTRAINT `books_ibfk_1` FOREIGN KEY (`CATEGORY_ID`) REFERENCES `book_category` (`CATEGORY_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=57 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of books
-- ----------------------------
INSERT INTO `books` VALUES ('54', '数据库', '王珊', '高等教育出版社', '3', '38.00元', '2014-12-15', '0', '1', '1');
INSERT INTO `books` VALUES ('55', '计算机网络', 'James F.Kurose', '高等教育出版社', '1', '59.00', '2014-12-17', null, '2', '1');
INSERT INTO `books` VALUES ('56', 'Effective C++', 'Scott Meyers', '电子工业出版社', '1', '`65.00', '2014-12-31', '1', '0', '1');

-- ----------------------------
-- Table structure for `book_category`
-- ----------------------------
DROP TABLE IF EXISTS `book_category`;
CREATE TABLE `book_category` (
  `CATEGORY_ID` int(11) NOT NULL AUTO_INCREMENT,
  `CATEGORY_NAME` varchar(255) NOT NULL,
  PRIMARY KEY (`CATEGORY_ID`),
  UNIQUE KEY `CATEGORY_NAME` (`CATEGORY_NAME`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of book_category
-- ----------------------------
INSERT INTO `book_category` VALUES ('8', '人文');
INSERT INTO `book_category` VALUES ('4', '农林');
INSERT INTO `book_category` VALUES ('3', '医学');
INSERT INTO `book_category` VALUES ('5', '建筑');
INSERT INTO `book_category` VALUES ('9', '科学');
INSERT INTO `book_category` VALUES ('6', '科普');
INSERT INTO `book_category` VALUES ('2', '自然科学');
INSERT INTO `book_category` VALUES ('1', '计算机技术');
INSERT INTO `book_category` VALUES ('7', '通信');

-- ----------------------------
-- Table structure for `borrow`
-- ----------------------------
DROP TABLE IF EXISTS `borrow`;
CREATE TABLE `borrow` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `READER_ID` int(11) NOT NULL,
  `BOOK_ID` int(11) NOT NULL,
  `DATE_BORROW` date NOT NULL,
  `DATE_RETURN` date NOT NULL,
  `LOSS` int(1) NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `READER_ID` (`READER_ID`),
  KEY `BOOK_ID` (`BOOK_ID`),
  CONSTRAINT `borrow_ibfk_3` FOREIGN KEY (`READER_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `borrow_ibfk_4` FOREIGN KEY (`BOOK_ID`) REFERENCES `unique_book` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of borrow
-- ----------------------------
INSERT INTO `borrow` VALUES ('15', '45', '66', '2014-12-18', '2014-12-19', '0');

-- ----------------------------
-- Table structure for `loss_reporting`
-- ----------------------------
DROP TABLE IF EXISTS `loss_reporting`;
CREATE TABLE `loss_reporting` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `READER_ID` int(11) NOT NULL,
  `LOSS_DATE` datetime NOT NULL,
  `REMARK` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  KEY `loss_reporting_ibfk_1` (`READER_ID`),
  CONSTRAINT `loss_reporting_ibfk_1` FOREIGN KEY (`READER_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of loss_reporting
-- ----------------------------

-- ----------------------------
-- Table structure for `managers`
-- ----------------------------
DROP TABLE IF EXISTS `managers`;
CREATE TABLE `managers` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `MANAGER_ID` int(11) NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `managers_ibfk_1` (`MANAGER_ID`),
  CONSTRAINT `managers_ibfk_1` FOREIGN KEY (`MANAGER_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of managers
-- ----------------------------
INSERT INTO `managers` VALUES ('1', '2');
INSERT INTO `managers` VALUES ('5', '42');

-- ----------------------------
-- Table structure for `member_level`
-- ----------------------------
DROP TABLE IF EXISTS `member_level`;
CREATE TABLE `member_level` (
  `LEVEL_ID` int(11) NOT NULL AUTO_INCREMENT,
  `LEVEL_NAME` varchar(255) NOT NULL,
  `DAYS` int(11) NOT NULL,
  `NUMBERS` int(11) NOT NULL,
  `FEE` double NOT NULL,
  PRIMARY KEY (`LEVEL_ID`),
  UNIQUE KEY `LEVEL_NAME` (`LEVEL_NAME`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of member_level
-- ----------------------------
INSERT INTO `member_level` VALUES ('1', '金卡', '60', '10', '100');
INSERT INTO `member_level` VALUES ('2', '银卡', '80', '10', '90');

-- ----------------------------
-- Table structure for `readers`
-- ----------------------------
DROP TABLE IF EXISTS `readers`;
CREATE TABLE `readers` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `READER_ID` int(11) NOT NULL,
  `CARD_NAME` varchar(255) NOT NULL,
  `CARD_ID` varchar(255) NOT NULL,
  `CARD_LEVEL` int(11) NOT NULL,
  `DAY` date NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `readers_ibfk_1` (`READER_ID`),
  KEY `CARD_LEVEL` (`CARD_LEVEL`),
  CONSTRAINT `readers_ibfk_1` FOREIGN KEY (`READER_ID`) REFERENCES `user` (`USER_ID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `readers_ibfk_2` FOREIGN KEY (`CARD_LEVEL`) REFERENCES `member_level` (`LEVEL_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of readers
-- ----------------------------
INSERT INTO `readers` VALUES ('18', '45', '1', '1', '1', '2014-12-17');

-- ----------------------------
-- Table structure for `unique_book`
-- ----------------------------
DROP TABLE IF EXISTS `unique_book`;
CREATE TABLE `unique_book` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `BOOK_CODE` varchar(255) NOT NULL,
  `BOOK_ID` int(11) NOT NULL,
  `ISBORROW` int(1) NOT NULL,
  `LASSBORROW` date DEFAULT NULL,
  `LASSRETURN` date DEFAULT NULL,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `BOOK_CODE` (`BOOK_CODE`),
  KEY `unique_book_ibfk_1` (`BOOK_ID`),
  CONSTRAINT `unique_book_ibfk_1` FOREIGN KEY (`BOOK_ID`) REFERENCES `books` (`BOOK_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=70 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of unique_book
-- ----------------------------
INSERT INTO `unique_book` VALUES ('66', 'database001', '54', '0', null, null);
INSERT INTO `unique_book` VALUES ('68', 'network001', '55', '0', null, null);
INSERT INTO `unique_book` VALUES ('69', '999', '56', '0', null, null);

-- ----------------------------
-- Table structure for `user`
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `USER_ID` int(11) NOT NULL AUTO_INCREMENT,
  `USER_CODE` varchar(255) NOT NULL,
  `USER_NAME` varchar(255) NOT NULL,
  `USER_PSW` varchar(255) NOT NULL,
  `SEX` tinyint(4) NOT NULL,
  `BIRTHDAY` date DEFAULT NULL,
  `PHONE` varchar(255) DEFAULT NULL,
  `MOBILE` varchar(255) DEFAULT NULL,
  `MAIL` varchar(255) DEFAULT NULL,
  `USER_TYPE` int(11) NOT NULL,
  `USER_REMARK` varchar(255) DEFAULT NULL,
  `USER_LASTLOGTIME` datetime DEFAULT NULL,
  `USER_CREATETIME` datetime DEFAULT NULL,
  PRIMARY KEY (`USER_ID`),
  UNIQUE KEY `USER_CODE` (`USER_CODE`),
  KEY `USER_TYPE` (`USER_TYPE`),
  CONSTRAINT `user_ibfk_1` FOREIGN KEY (`USER_TYPE`) REFERENCES `user_type` (`USER_TYPE_ID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=46 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('2', '12281116', '卢秋明', '050daf3602c1364620a3db6927968132', '0', '2000-01-06', '18811437370', '18811437370', '', '1', 'test', '2014-12-31 16:08:43', null);
INSERT INTO `user` VALUES ('42', '12281117', '马超', '81dc9bdb52d04dc20036dbd8313ed055', '0', '1993-06-08', '133', '122', '', '2', '', '2014-12-17 15:51:38', '2014-12-17 15:36:05');
INSERT INTO `user` VALUES ('45', '12345', '12345', '81dc9bdb52d04dc20036dbd8313ed055', '0', '2000-01-01', '', '', '', '3', '', '2014-12-31 15:49:22', null);

-- ----------------------------
-- Table structure for `user_type`
-- ----------------------------
DROP TABLE IF EXISTS `user_type`;
CREATE TABLE `user_type` (
  `USER_TYPE_ID` int(11) NOT NULL AUTO_INCREMENT,
  `USER_TYPE_NAME` varchar(255) NOT NULL,
  PRIMARY KEY (`USER_TYPE_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user_type
-- ----------------------------
INSERT INTO `user_type` VALUES ('1', '超级管理员');
INSERT INTO `user_type` VALUES ('2', '管理员');
INSERT INTO `user_type` VALUES ('3', '读者');

-- ----------------------------
-- Procedure structure for `BOOKS_INSERT_PROC`
-- ----------------------------
DROP PROCEDURE IF EXISTS `BOOKS_INSERT_PROC`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `BOOKS_INSERT_PROC`(IN `d_BOOK_NAME` varchar(255),IN `d_AUTHOR` varchar(255),IN `d_PUBLISHING` varchar(255),IN `d_CATEGORY_ID` int(11),IN `d_PRICE` varchar(255),IN `d_DATE_IN` date,IN `d_QUANTITY_IN` int(11),IN `d_QUANTITY_OUT` int(11),IN `d_QUANTITY` int(11), OUT `d_BOOK_ID` int)
BEGIN
	
	INSERT INTO books(BOOK_NAME, AUTHOR, PUBLISHING, CATEGORY_ID, PRICE, DATE_IN, QUANTITY_IN, QUANTITY_OUT, QUANTITY)
	VALUES(d_BOOK_NAME, d_AUTHOR, d_PUBLISHING, d_CATEGORY_ID, d_PRICE, d_DATE_IN, d_QUANTITY_IN, d_QUANTITY_OUT, d_QUANTITY);

	SELECT MAX(book_id) FROM books INTO d_BOOK_ID;

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `BOOK_CATEGORY_INSERT_PROC`
-- ----------------------------
DROP PROCEDURE IF EXISTS `BOOK_CATEGORY_INSERT_PROC`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `BOOK_CATEGORY_INSERT_PROC`(IN `d_CATEGORY_NAME` varchar(255),OUT `d_CATEGORY_ID` int(11))
BEGIN
	
	INSERT INTO book_category(CATEGORY_ID, CATEGORY_NAME)
	VALUES(d_CATEGORY_ID, d_CATEGORY_NAME);

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `BORROW_INSERT_PROC`
-- ----------------------------
DROP PROCEDURE IF EXISTS `BORROW_INSERT_PROC`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `BORROW_INSERT_PROC`(IN `d_READER_ID` int(11),IN `d_BOOK_ID` int(11),IN `d_DATE_BORROW` date,IN `d_DATE_RETURN` date,IN `d_LOSS` int(1),OUT `d_ID` int(11))
BEGIN
	
	INSERT INTO borrow(ID, READER_ID, BOOK_ID, DATE_BORROW, DATE_RETURN, LOSS)
	VALUES(d_ID, d_READER_ID, d_BOOK_ID, d_DATE_BORROW, d_DATE_RETURN, d_LOSS);

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `LOSS_REPORTING_INSERT_PROC`
-- ----------------------------
DROP PROCEDURE IF EXISTS `LOSS_REPORTING_INSERT_PROC`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `LOSS_REPORTING_INSERT_PROC`(IN `d_READER_ID` int(11),IN `d_LOSS_DATE` datetime,IN `d_REMARK` varchar(255),OUT `d_ID` int(11))
BEGIN
	
	INSERT INTO loss_reporting(ID, READER_ID, LOSS_DATE, REMARK)
	VALUES(d_ID, d_READER_ID, d_LOSS_DATE, d_REMARK);

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `MANAGERS_INSERT_PROC`
-- ----------------------------
DROP PROCEDURE IF EXISTS `MANAGERS_INSERT_PROC`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `MANAGERS_INSERT_PROC`(IN `d_MANAGER_ID` int(11),OUT `d_ID` int(11))
BEGIN
	
	INSERT INTO managers(ID, MANAGER_ID)
	VALUES(d_ID, d_MANAGER_ID);

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `MEMBER_LEVEL_INSERT_PROC`
-- ----------------------------
DROP PROCEDURE IF EXISTS `MEMBER_LEVEL_INSERT_PROC`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `MEMBER_LEVEL_INSERT_PROC`(IN `d_LEVEL_NAME` varchar(255),IN `d_DAYS` int(11),IN `d_NUMBERS` int(11),IN `d_FEE` double,OUT `d_LEVEL_ID` int(11))
BEGIN
	
	INSERT INTO member_level(LEVEL_ID, LEVEL_NAME, DAYS, NUMBERS, FEE)
	VALUES(d_LEVEL_ID, d_LEVEL_NAME, d_DAYS, d_NUMBERS, d_FEE);

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `READERS_INSERT_PROC`
-- ----------------------------
DROP PROCEDURE IF EXISTS `READERS_INSERT_PROC`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `READERS_INSERT_PROC`(IN `d_READER_ID` int(11),IN `d_CARD_NAME` varchar(255),IN `d_CARD_ID` varchar(255),IN `d_CARD_LEVEL` int(11),IN `d_DAY` date,OUT `d_ID` int(11))
BEGIN
	
	INSERT INTO readers (ID,READER_ID,CARD_NAME,CARD_ID,CARD_LEVEL,DAY)
	VALUES(d_ID,d_READER_ID,d_CARD_NAME,d_CARD_ID,d_CARD_LEVEL,d_DAY);

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `UNIQUE_BOOK_INSERT_PROC`
-- ----------------------------
DROP PROCEDURE IF EXISTS `UNIQUE_BOOK_INSERT_PROC`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `UNIQUE_BOOK_INSERT_PROC`(IN `d_BOOK_CODE` varchar(255),IN `d_BOOK_ID` int(11),IN `d_ISBORROW` int(1),IN `d_LASSBORROW` date,IN `d_LASSRETURN` date,OUT `d_ID` int(11))
BEGIN
	
	INSERT INTO unique_book(ID, BOOK_CODE, BOOK_ID, ISBORROW, LASSBORROW, LASSRETURN)
	VALUES(d_ID, d_BOOK_CODE, d_BOOK_ID, d_ISBORROW, d_LASSBORROW, d_LASSRETURN);

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `USER_INSERT_PROC`
-- ----------------------------
DROP PROCEDURE IF EXISTS `USER_INSERT_PROC`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `USER_INSERT_PROC`(IN `d_CODE` varchar(255),IN `d_NAME` varchar(255),IN `d_PSW` varchar(255),IN `d_SEX` tinyint(4),IN `d_BIRTHDAY` date,IN `d_PHONE` varchar(255),IN `d_MOBILE` varchar(255),IN `d_MAIL` varchar(255),IN `d_USERTYPE` int(11),IN `d_USERREMARK` varchar(255),IN `d_LASTLOGTIME` datetime,IN `d_CREATETIME` datetime,OUT `d_ID` int(10))
BEGIN

	INSERT INTO	USER(USER_ID,USER_CODE,USER_NAME,USER_PSW,SEX,BIRTHDAY,PHONE,MOBILE,MAIL,USER_TYPE,USER_REMARK,USER_LASTLOGTIME,USER_CREATETIME) 
  VALUES (d_ID,d_CODE,d_NAME,d_PSW,d_SEX,d_BIRTHDAY,d_PHONE,d_MOBILE,d_MAIL,d_USERTYPE,d_USERREMARK,d_LASTLOGTIME,d_CREATETIME);

END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `USER_TYPE_INSERT_PROC`
-- ----------------------------
DROP PROCEDURE IF EXISTS `USER_TYPE_INSERT_PROC`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `USER_TYPE_INSERT_PROC`(IN `d_USER_TYPE_NAME` VARCHAR(255),OUT `d_USER_TYPE_ID` INT(11))
BEGIN

	INSERT INTO USER_TYPE(USER_TYPE_NAME) 
	VALUES(d_USER_TYPE_NAME);

	SELECT MAX(user_type_id) FROM user_type INTO d_USER_TYPE_ID;
	SELECT d_USER_TYPE_ID;

END
;;
DELIMITER ;
