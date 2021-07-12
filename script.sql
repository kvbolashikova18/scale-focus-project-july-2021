USE [master]
GO
/****** Object:  Database [Team Management]    Script Date: 7/12/2021 3:11:02 PM ******/
CREATE DATABASE [Team Management]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'Team Management', FILENAME = N'C:\Users\kvbolashikova18\Team Management.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'Team Management_log', FILENAME = N'C:\Users\kvbolashikova18\Team Management_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [Team Management].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [Team Management] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [Team Management] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [Team Management] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [Team Management] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [Team Management] SET ARITHABORT OFF 
GO
ALTER DATABASE [Team Management] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [Team Management] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [Team Management] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [Team Management] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [Team Management] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [Team Management] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [Team Management] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [Team Management] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [Team Management] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [Team Management] SET  DISABLE_BROKER 
GO
ALTER DATABASE [Team Management] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [Team Management] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [Team Management] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [Team Management] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [Team Management] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [Team Management] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [Team Management] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [Team Management] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [Team Management] SET  MULTI_USER 
GO
ALTER DATABASE [Team Management] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [Team Management] SET DB_CHAINING OFF 
GO
ALTER DATABASE [Team Management] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [Team Management] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [Team Management] SET DELAYED_DURABILITY = DISABLED 
GO
USE [Team Management]
GO
/****** Object:  Table [dbo].[Logs]    Script Date: 7/12/2021 3:11:02 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Logs](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Id of Task] [int] NOT NULL,
	[Id of User] [int] NOT NULL,
	[Time] [int] NOT NULL,
	[Date] [datetime] NOT NULL,
 CONSTRAINT [PK_Logs] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Projects]    Script Date: 7/12/2021 3:11:02 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Projects](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Title] [nvarchar](50) NOT NULL,
	[Description] [nvarchar](100) NOT NULL,
	[Date of creation] [datetime] NOT NULL,
	[Id of creator] [int] NOT NULL,
	[Date of last change] [datetime] NOT NULL,
	[Id of changer] [int] NOT NULL,
 CONSTRAINT [PK_Projects] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ProjectsTeams]    Script Date: 7/12/2021 3:11:02 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ProjectsTeams](
	[Project Id] [int] NOT NULL,
	[Team Id] [int] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Tasks]    Script Date: 7/12/2021 3:11:02 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Tasks](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Id of Project] [int] NOT NULL,
	[Id of Assignee] [int] NOT NULL,
	[Title] [nvarchar](50) NOT NULL,
	[Description] [nvarchar](100) NOT NULL,
	[Status] [tinyint] NOT NULL,
	[Date of creation] [datetime] NOT NULL,
	[Id of creator] [int] NOT NULL,
	[Date of last change] [datetime] NOT NULL,
	[Id of changer] [int] NOT NULL,
 CONSTRAINT [PK_Tasks] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Teams]    Script Date: 7/12/2021 3:11:02 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Teams](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Title] [nvarchar](50) NOT NULL,
	[Date of creation] [datetime] NOT NULL,
	[Id of creator] [int] NOT NULL,
	[Date of last change] [datetime] NOT NULL,
	[Id of changer] [int] NOT NULL,
 CONSTRAINT [PK_Teams] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Users]    Script Date: 7/12/2021 3:11:02 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Users](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Username] [nvarchar](50) NOT NULL,
	[Password] [nvarchar](50) NOT NULL,
	[First Name] [nvarchar](50) NOT NULL,
	[Last Name] [nvarchar](50) NOT NULL,
	[Date of creation] [datetime] NOT NULL,
	[Id of creator] [int] NULL,
	[Date of last change] [datetime] NOT NULL,
	[Id of changer] [int] NULL,
	[isAdmin] [bit] NULL,
 CONSTRAINT [PK_Users] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UsersTeams]    Script Date: 7/12/2021 3:11:02 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UsersTeams](
	[User Id] [int] NOT NULL,
	[Team Id] [int] NOT NULL
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[Logs] ON 

INSERT [dbo].[Logs] ([Id], [Id of Task], [Id of User], [Time], [Date]) VALUES (3, 1, 11, 3, CAST(N'2021-07-12T12:18:23.633' AS DateTime))
INSERT [dbo].[Logs] ([Id], [Id of Task], [Id of User], [Time], [Date]) VALUES (4, 1, 11, 2, CAST(N'2021-07-12T12:18:48.090' AS DateTime))
SET IDENTITY_INSERT [dbo].[Logs] OFF
GO
SET IDENTITY_INSERT [dbo].[Projects] ON 

INSERT [dbo].[Projects] ([Id], [Title], [Description], [Date of creation], [Id of creator], [Date of last change], [Id of changer]) VALUES (1, N'Animals', N'description 1', CAST(N'2021-07-12T11:14:36.347' AS DateTime), 10, CAST(N'2021-07-12T11:14:36.347' AS DateTime), 10)
INSERT [dbo].[Projects] ([Id], [Title], [Description], [Date of creation], [Id of creator], [Date of last change], [Id of changer]) VALUES (2, N'Studio', N'description 2', CAST(N'2021-07-12T11:15:38.047' AS DateTime), 10, CAST(N'2021-07-12T11:15:38.047' AS DateTime), 10)
INSERT [dbo].[Projects] ([Id], [Title], [Description], [Date of creation], [Id of creator], [Date of last change], [Id of changer]) VALUES (3, N'History', N'description 3', CAST(N'2021-07-12T11:15:58.983' AS DateTime), 10, CAST(N'2021-07-12T11:15:58.983' AS DateTime), 10)
SET IDENTITY_INSERT [dbo].[Projects] OFF
GO
SET IDENTITY_INSERT [dbo].[Tasks] ON 

INSERT [dbo].[Tasks] ([Id], [Id of Project], [Id of Assignee], [Title], [Description], [Status], [Date of creation], [Id of creator], [Date of last change], [Id of changer]) VALUES (1, 1, 11, N'title 1', N'des 1', 0, CAST(N'2021-07-12T11:40:52.847' AS DateTime), 10, CAST(N'2021-07-12T11:40:52.847' AS DateTime), 10)
INSERT [dbo].[Tasks] ([Id], [Id of Project], [Id of Assignee], [Title], [Description], [Status], [Date of creation], [Id of creator], [Date of last change], [Id of changer]) VALUES (2, 1, 12, N'title 2', N'des 2', 1, CAST(N'2021-07-12T11:41:41.000' AS DateTime), 10, CAST(N'2021-07-12T11:41:41.000' AS DateTime), 10)
SET IDENTITY_INSERT [dbo].[Tasks] OFF
GO
SET IDENTITY_INSERT [dbo].[Teams] ON 

INSERT [dbo].[Teams] ([Id], [Title], [Date of creation], [Id of creator], [Date of last change], [Id of changer]) VALUES (2, N'Dream team', CAST(N'2021-07-09T10:13:59.127' AS DateTime), 10, CAST(N'2021-07-09T10:13:59.127' AS DateTime), 10)
INSERT [dbo].[Teams] ([Id], [Title], [Date of creation], [Id of creator], [Date of last change], [Id of changer]) VALUES (3, N'Ninjas', CAST(N'2021-07-09T10:14:54.720' AS DateTime), 11, CAST(N'2021-07-09T10:14:54.720' AS DateTime), 11)
INSERT [dbo].[Teams] ([Id], [Title], [Date of creation], [Id of creator], [Date of last change], [Id of changer]) VALUES (4, N'Titans', CAST(N'2021-07-09T10:15:15.593' AS DateTime), 12, CAST(N'2021-07-09T10:15:15.593' AS DateTime), 12)
SET IDENTITY_INSERT [dbo].[Teams] OFF
GO
SET IDENTITY_INSERT [dbo].[Users] ON 

INSERT [dbo].[Users] ([Id], [Username], [Password], [First Name], [Last Name], [Date of creation], [Id of creator], [Date of last change], [Id of changer], [isAdmin]) VALUES (10, N'admin', N'adminpass', N'admin', N'admin', CAST(N'2021-07-08T10:40:20.643' AS DateTime), NULL, CAST(N'2021-07-08T10:40:20.643' AS DateTime), NULL, 1)
INSERT [dbo].[Users] ([Id], [Username], [Password], [First Name], [Last Name], [Date of creation], [Id of creator], [Date of last change], [Id of changer], [isAdmin]) VALUES (11, N'username2', N'userpass2', N'user2', N'user2', CAST(N'2021-07-08T10:41:46.800' AS DateTime), 10, CAST(N'2021-07-08T10:41:46.800' AS DateTime), 10, 0)
INSERT [dbo].[Users] ([Id], [Username], [Password], [First Name], [Last Name], [Date of creation], [Id of creator], [Date of last change], [Id of changer], [isAdmin]) VALUES (12, N'username3', N'userpass3', N'user3', N'user3', CAST(N'2021-07-08T10:48:35.813' AS DateTime), 10, CAST(N'2021-07-08T10:48:35.813' AS DateTime), 10, 0)
INSERT [dbo].[Users] ([Id], [Username], [Password], [First Name], [Last Name], [Date of creation], [Id of creator], [Date of last change], [Id of changer], [isAdmin]) VALUES (13, N'username4', N'userpass4', N'user4', N'user4', CAST(N'2021-07-08T14:05:41.613' AS DateTime), 10, CAST(N'2021-07-08T14:05:41.613' AS DateTime), 10, 0)
SET IDENTITY_INSERT [dbo].[Users] OFF
GO
ALTER TABLE [dbo].[Logs] ADD  CONSTRAINT [DF_Logs_Date]  DEFAULT (getdate()) FOR [Date]
GO
ALTER TABLE [dbo].[Projects] ADD  CONSTRAINT [DF_Projects_Date of creation]  DEFAULT (getdate()) FOR [Date of creation]
GO
ALTER TABLE [dbo].[Projects] ADD  CONSTRAINT [DF_Projects_Date of last change]  DEFAULT (getdate()) FOR [Date of last change]
GO
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_Date of creation]  DEFAULT (getdate()) FOR [Date of creation]
GO
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_Date of last change]  DEFAULT (getdate()) FOR [Date of last change]
GO
ALTER TABLE [dbo].[Teams] ADD  CONSTRAINT [DF_Teams_Date of creation]  DEFAULT (getdate()) FOR [Date of creation]
GO
ALTER TABLE [dbo].[Teams] ADD  CONSTRAINT [DF_Teams_Date of last change]  DEFAULT (getdate()) FOR [Date of last change]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_Date of creation]  DEFAULT (getdate()) FOR [Date of creation]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_Date of last change]  DEFAULT (getdate()) FOR [Date of last change]
GO
ALTER TABLE [dbo].[Logs]  WITH CHECK ADD  CONSTRAINT [FK_Logs_Tasks] FOREIGN KEY([Id of Task])
REFERENCES [dbo].[Tasks] ([Id])
GO
ALTER TABLE [dbo].[Logs] CHECK CONSTRAINT [FK_Logs_Tasks]
GO
ALTER TABLE [dbo].[Logs]  WITH CHECK ADD  CONSTRAINT [FK_Logs_Users] FOREIGN KEY([Id of User])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Logs] CHECK CONSTRAINT [FK_Logs_Users]
GO
ALTER TABLE [dbo].[Projects]  WITH CHECK ADD  CONSTRAINT [FK_Projects_Users] FOREIGN KEY([Id of creator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Projects] CHECK CONSTRAINT [FK_Projects_Users]
GO
ALTER TABLE [dbo].[Projects]  WITH CHECK ADD  CONSTRAINT [FK_Projects_Users1] FOREIGN KEY([Id of changer])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Projects] CHECK CONSTRAINT [FK_Projects_Users1]
GO
ALTER TABLE [dbo].[ProjectsTeams]  WITH CHECK ADD  CONSTRAINT [FK_ProjectsTeams_Projects] FOREIGN KEY([Project Id])
REFERENCES [dbo].[Projects] ([Id])
GO
ALTER TABLE [dbo].[ProjectsTeams] CHECK CONSTRAINT [FK_ProjectsTeams_Projects]
GO
ALTER TABLE [dbo].[ProjectsTeams]  WITH CHECK ADD  CONSTRAINT [FK_ProjectsTeams_Teams] FOREIGN KEY([Team Id])
REFERENCES [dbo].[Teams] ([Id])
GO
ALTER TABLE [dbo].[ProjectsTeams] CHECK CONSTRAINT [FK_ProjectsTeams_Teams]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Tasks_Projects] FOREIGN KEY([Id of Project])
REFERENCES [dbo].[Projects] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Tasks_Projects]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Tasks_Users] FOREIGN KEY([Id of Assignee])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Tasks_Users]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Tasks_Users1] FOREIGN KEY([Id of creator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Tasks_Users1]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Tasks_Users2] FOREIGN KEY([Id of changer])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Tasks_Users2]
GO
ALTER TABLE [dbo].[Teams]  WITH CHECK ADD  CONSTRAINT [FK_Teams_Users] FOREIGN KEY([Id of creator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Teams] CHECK CONSTRAINT [FK_Teams_Users]
GO
ALTER TABLE [dbo].[Teams]  WITH CHECK ADD  CONSTRAINT [FK_Teams_Users1] FOREIGN KEY([Id of changer])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Teams] CHECK CONSTRAINT [FK_Teams_Users1]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_Users_Users] FOREIGN KEY([Id of creator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_Users_Users]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_Users_Users1] FOREIGN KEY([Id of changer])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_Users_Users1]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_Teams] FOREIGN KEY([Team Id])
REFERENCES [dbo].[Teams] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_Teams]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_Users] FOREIGN KEY([User Id])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_Users]
GO
USE [master]
GO
ALTER DATABASE [Team Management] SET  READ_WRITE 
GO
