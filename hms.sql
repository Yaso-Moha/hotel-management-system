-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 15, 2024 at 02:40 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.0.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `hms`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `Admin_ID` varchar(5) NOT NULL,
  `Admin_name` varchar(25) NOT NULL,
  `Admin_username` varchar(15) NOT NULL,
  `Admin_password` varchar(35) NOT NULL,
  `Admin_address` varchar(60) NOT NULL,
  `Admin_phonenumber` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`Admin_ID`, `Admin_name`, `Admin_username`, `Admin_password`, `Admin_address`, `Admin_phonenumber`) VALUES
('13444', 'Yaseen Mohamed', '&Yaseen', 'Yaseen2212', 'The heigts residence ', '0167084608');

-- --------------------------------------------------------

--
-- Table structure for table `booking`
--

CREATE TABLE `booking` (
  `Booking_ID` varchar(5) NOT NULL,
  `Guest_username` varchar(15) NOT NULL,
  `Checkin_date` varchar(15) NOT NULL,
  `Checkout_date` varchar(15) NOT NULL,
  `Room_ID` varchar(5) NOT NULL,
  `Total_cost` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `booking`
--

INSERT INTO `booking` (`Booking_ID`, `Guest_username`, `Checkin_date`, `Checkout_date`, `Room_ID`, `Total_cost`) VALUES
('10058', 'Rony', '2024-01-01', '2024-01-09', '10058', '3060'),
('12106', 'Patricia', '2024-04-08', '2024-04-12', '12106', '600.000000'),
('12580', 'Patricia', '2024-04-02', '2024-04-03', '12580', '250.000000'),
('12926', 'alice123', '2024-04-15', '2024-04-21', '12926', '1200.000000'),
('12991', 'alice123', '2024-04-05', '2024-04-09', '12991', '400.000000'),
('13474', 'andrew99', '2024-04-20', '2024-04-22', '13474', '600.000000'),
('13549', 'Taleb', '2024-02-05', '2024-02-15', '13549', '2500.000000'),
('13585', 'andrew99', '2024-04-25', '2024-04-28', '13585', '1500.000000'),
('13807', 'andrew99', '2024-04-06', '2024-04-09', '13807', '300.000000'),
('14078', 'Yousf', '2024-03-15', '2024-03-18', '14078', '600.000000'),
('14124', 'sarah', '2024-04-13', '2024-04-23', '14124', '2000.000000'),
('14140', 'Yousf', '2024-02-02', '2024-02-05', '14140', '300.000000'),
('14193', 'sarah', '2024-05-05', '2024-05-08', '14193', '750.000000'),
('14732', 'samuel34', '2024-05-01', '2024-05-04', '14732', '900.000000'),
('14784', 'samuel34', '2024-05-25', '2024-05-30', '14784', '500.000000'),
('14806', 'Uri', '2024-03-12', '2024-03-17', '14806', '500.000000'),
('14891', 'Uri', '2024-03-29', '2024-03-30', '14891', '300.000000'),
('15097', 'davidm22', '2024-05-15', '2024-05-19', '15097', '400.000000'),
('15137', 'davidm22', '2024-05-09', '2024-05-11', '15137', '500.000000'),
('15355', 'iskandar', '2024-03-05', '2024-03-13', '15355', '1600.000000'),
('15375', 'diana_77', '2024-05-19', '2024-05-26', '15375', '1260.000000'),
('15453', 'iskandar', '2024-03-22', '2024-03-23', '15453', '500.000000'),
('15568', 'diana_77', '2024-05-28', '2024-05-31', '15568', '600.000000'),
('15881', 'frank_56', '2024-05-03', '2024-05-06', '15881', '1500.000000'),
('15940', 'frank_56', '2024-05-19', '2024-05-27', '15940', '800.000000'),
('16453', 'fiona2014', '2024-06-25', '2024-06-30', '16453', '750.000000'),
('16531', 'fiona2014', '2024-06-06', '2024-06-08', '16531', '400.000000'),
('16903', 'george_89', '2024-06-15', '2024-06-19', '16903', '720.000000'),
('16955', 'george_89', '2024-06-01', '2024-06-04', '16955', '450.000000'),
('17367', 'gracelove', '2024-06-10', '2024-06-14', '17367', '1200.000000'),
('17416', 'gracelove', '2024-06-23', '2024-06-25', '17416', '200.000000'),
('17729', 'henry001', '2024-07-01', '2024-07-14', '17729', '3250.000000'),
('17782', 'henry001', '2024-07-27', '2024-07-30', '17782', '300.000000'),
('18177', 'hannahb', '2024-07-02', '2024-07-04', '18177', '400.000000'),
('18229', 'hannahb', '2024-07-20', '2024-07-25', '18229', '750.000000'),
('18853', 'Johne', '2024-07-13', '2024-07-16', '18853', '900.000000'),
('18921', 'Johne', '2024-07-01', '2024-07-09', '18921', '1600.000000'),
('19643', 'jenni_21', '2024-07-09', '2024-07-13', '19643', '1000.000000'),
('19780', 'jenni_21', '2024-07-17', '2024-07-21', '19780', '600.000000'),
('21072', 'Waleed', '2024-01-03', '2024-01-06', '21072', '300.000000'),
('21291', 'Waleed', '2024-01-10', '2024-01-11', '21291', '250.000000'),
('21794', 'Eslam', '2024-02-15', '2024-02-20', '21794', '750.000000'),
('21856', 'Eslam', '2024-01-04', '2024-01-06', '21856', '400.000000'),
('22682', 'Rony', '2024-01-20', '2024-01-23', '22682', '540.000000'),
('29432', 'pauls', '2024-04-01', '2024-04-03', '29432', '200.000000');

-- --------------------------------------------------------

--
-- Table structure for table `guest`
--

CREATE TABLE `guest` (
  `Guest_ID` varchar(15) NOT NULL,
  `Guest_name` varchar(25) NOT NULL,
  `Guest_username` varchar(15) NOT NULL,
  `Guest_password` varchar(35) NOT NULL,
  `Guest_address` varchar(60) DEFAULT NULL,
  `Guest_phonenumber` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `guest`
--

INSERT INTO `guest` (`Guest_ID`, `Guest_name`, `Guest_username`, `Guest_password`, `Guest_address`, `Guest_phonenumber`) VALUES
('12700', 'Alisson monika', 'alice123', 'border', '789 Oak Drive, Austin, TX', '08371934'),
('13318', 'Andrew tate', 'andrew99', 'tate', '101 Birch Lane, Atlanta, GA', '028347234'),
('14866', 'David james', 'davidm22', 'tornado', '404 Pine Court, Denver, CO', '0426859274'),
('15208', 'Diana moretana', 'diana_77', 'prince', '505 Walnut Street, Dallas, TX', '0482761849'),
('21418', 'Eslam Mohamed', 'Eslam', 'tron', 'De centrum', '013759305'),
('16106', 'Fiona lisa', 'fiona2014', 'fronka', '707 Willow Lane, Fresno, CA', '05873885'),
('15662', 'Frank reprey', 'frank_56', 'cancel', '606 Spruce Road, Fort Worth, TX', '0487875923'),
('16596', 'George mohand', 'george_89', 'mommy', '808 Maple Boulevard, Grand Rapids, MI', '0872984242'),
('17021', 'Grace lacer', 'gracelove', 'hater', '909 Cedar Avenue, Greensboro, NC', '0387343234'),
('17857', 'Hannah Hanan', 'hannahb', 'honey', '222 Elm Drive, Honolulu, HI', '0986545433'),
('17498', 'henry tary', 'henry001', 'cruse', '111 Holly Street, Houston, TX', '038378493'),
('15103', 'iskandar abduallh', 'iskandar', 'soso', 'The heights residence ', '0748937123'),
('19268', 'Jennifer alison', 'jenni_21', 'loston', '444 Cedar Road, Jersey City, NJ', '0498247234'),
('18386', 'john doe', 'Johne', 'sins', '333 Palm Lane, Jacksonville, FL', '0983745321'),
('26178', 'Oppa lamar', 'Opaa', '9487', 'Sarawk', '02649163'),
('11571', 'patrik lary', 'Patricia', 'gorm', '456 Maple Avenue, Pasadena, CA', '0483849274'),
('28837', 'paul smith', 'pauls', 'ploto', '123 Pine Street, Portland, OR', '0382784992'),
('21954', 'Rony moi', 'Rony', 'rani', 'Halo hostel', '049385612'),
('14268', 'samuel jackson', 'samuel34', 'pepper', '303 Elm Avenue, San Francisco, CA', '0382745962'),
('13902', 'Sarah Jane', 'Sarah', 'spider', '202 Cedar Street, Seattle, WA', '0486926495'),
('10146', 'Taleb khaled', 'Taleb', 'ninja', 'Newyork', '0392746281'),
('14672', 'uri lai', 'Uri', '084', 'BBU', '016747293'),
('20847', 'Waleed iskandar', 'Waleed', '1571', 'University hostel', '019683548'),
('13957', 'yousef ali', 'Yousf', 'yoyo', 'BBU', '0947284728');

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `Payment_ID` varchar(5) NOT NULL,
  `Payment_method` varchar(15) NOT NULL,
  `Booking_ID` varchar(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `payment`
--

INSERT INTO `payment` (`Payment_ID`, `Payment_method`, `Booking_ID`) VALUES
('10045', 'PayPal', '22682'),
('10133', 'Cash', '10058'),
('12201', 'Debit Card', '12106'),
('12645', 'PayPal', '12580'),
('12981', 'Cash', '12926'),
('13056', 'Credit Card', '12991'),
('13543', 'Credit Card', '13474'),
('13654', 'PayPal', '13585'),
('13889', 'Credit Card', '13807'),
('13921', 'Debit Card', '13549'),
('14140', 'Credit Card', '14078'),
('14190', 'PayPal', '14124'),
('14252', 'Credit Card', '14193'),
('14643', 'Debit Card', '14140'),
('14777', 'Cash', '14732'),
('14846', 'PayPal', '14784'),
('14884', 'PayPal', '14806'),
('15087', 'Cash', '14891'),
('15133', 'Credit Card', '15097'),
('15186', 'Credit Card', '15137'),
('15440', 'Cash', '15375'),
('15443', 'PayPal', '15355'),
('15495', 'PayPal', '15453'),
('15630', 'PayPal', '15568'),
('15937', 'Cash', '15881'),
('15999', 'Debit Card', '15940'),
('16531', 'Credit Card', '16453'),
('16583', 'PayPal', '16531'),
('16949', 'PayPal', '16903'),
('17004', 'Credit Card', '16955'),
('17406', 'Credit Card', '17367'),
('17484', 'PayPal', '17416'),
('17778', 'Credit Card', '17729'),
('17840', 'Credit Card', '17782'),
('18223', 'Credit Card', '18177'),
('18298', 'PayPal', '18229'),
('18918', 'Cash', '18853'),
('18980', 'Credit Card', '18921'),
('19695', 'PayPal', '19643'),
('19832', 'Credit Card', '19780'),
('21255', 'Credit Card', '21072'),
('21379', 'Credit Card', '21291'),
('21853', 'Debit Card', '21794'),
('21938', 'Cash', '21856'),
('29781', 'Credit Card', '29432');

-- --------------------------------------------------------

--
-- Table structure for table `room`
--

CREATE TABLE `room` (
  `Room_ID` varchar(5) NOT NULL,
  `Room_type` varchar(15) NOT NULL,
  `Room_number` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `room`
--

INSERT INTO `room` (`Room_ID`, `Room_type`, `Room_number`) VALUES
('10058', 'Presidental Sui', '158'),
('10525', 'Double Room', '625'),
('12106', 'Double Room', '606'),
('12580', 'Suite', '180'),
('12631', 'Executive Suite', '931'),
('12926', 'Deluxe Room', '526'),
('12991', 'Single Room', '591'),
('13474', 'Executive Suite', '174'),
('13549', 'Suite', '949'),
('13585', 'Presidental Sui', '285'),
('13807', 'Single Room', '507'),
('14078', 'Deluxe Room', '578'),
('14124', 'Deluxe Room', '824'),
('14140', 'Single Room', '640'),
('14193', 'Suite', '893'),
('14732', 'Executive Suite', '532'),
('14784', 'Single Room', '584'),
('14806', 'Single Room', '406'),
('14891', 'Executive Suite', '491'),
('15097', 'Single Room', '897'),
('15137', 'Suite', '937'),
('15355', 'Deluxe Room', '955'),
('15375', 'Family Room', '275'),
('15453', 'Presidental Sui', '153'),
('15568', 'Deluxe Room', '468'),
('15881', 'Presidental Sui', '781'),
('15940', 'Single Room', '840'),
('16453', 'Double Room', '453'),
('16531', 'Deluxe Room', '531'),
('16903', 'Family Room', '903'),
('16955', 'Double Room', '959'),
('17367', 'Executive Suite', '467'),
('17416', 'Single Room', '516'),
('17729', 'Suite', '829'),
('17782', 'Single Room', '882'),
('18177', 'Deluxe Room', '377'),
('18229', 'Double Room', '429'),
('18853', 'Executive Suite', '156'),
('18921', 'Deluxe Room', '221'),
('19643', 'Suite', '943'),
('19780', 'Double Room', '183'),
('21072', 'Single Room', '572'),
('21291', 'Suite', '791'),
('21794', 'Double Room', '394'),
('21856', 'Deluxe Room', '456'),
('22682', 'Family Room', '382'),
('29432', 'Single Room', '632');

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE `staff` (
  `Sfaff_ID` varchar(5) NOT NULL,
  `Staff_name` varchar(25) NOT NULL,
  `Staff_username` varchar(15) NOT NULL,
  `Staff_password` varchar(35) NOT NULL,
  `Staff_address` varchar(60) NOT NULL,
  `Staff_phonenumber` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`Sfaff_ID`, `Staff_name`, `Staff_username`, `Staff_password`, `Staff_address`, `Staff_phonenumber`) VALUES
('18172', 'Sharif hamad', '$Sharif', 'shifu', 'Atlantis', '0863293652'),
('22836', 'Anas saied', '$Lamak', 'loid', 'putrajaya', '0648958264');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`Admin_ID`),
  ADD UNIQUE KEY `Admin_username` (`Admin_username`);

--
-- Indexes for table `booking`
--
ALTER TABLE `booking`
  ADD PRIMARY KEY (`Booking_ID`),
  ADD KEY `FK_Guest_username` (`Guest_username`) USING BTREE,
  ADD KEY `FK_Room_ID` (`Room_ID`);

--
-- Indexes for table `guest`
--
ALTER TABLE `guest`
  ADD PRIMARY KEY (`Guest_username`),
  ADD UNIQUE KEY `Guest_username` (`Guest_username`),
  ADD UNIQUE KEY `Guest_ID` (`Guest_ID`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`Payment_ID`),
  ADD KEY `FK_Booking_ID` (`Booking_ID`);

--
-- Indexes for table `room`
--
ALTER TABLE `room`
  ADD PRIMARY KEY (`Room_ID`),
  ADD UNIQUE KEY `Room_number` (`Room_number`);

--
-- Indexes for table `staff`
--
ALTER TABLE `staff`
  ADD PRIMARY KEY (`Sfaff_ID`),
  ADD UNIQUE KEY `Staff_username` (`Staff_username`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `booking`
--
ALTER TABLE `booking`
  ADD CONSTRAINT `FK_Room_ID` FOREIGN KEY (`Room_ID`) REFERENCES `room` (`Room_ID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `payment`
--
ALTER TABLE `payment`
  ADD CONSTRAINT `FK_Booking_ID` FOREIGN KEY (`Booking_ID`) REFERENCES `booking` (`Booking_ID`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
