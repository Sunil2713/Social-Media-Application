# Social Media Application

A simple social media application implemented in C that simulates basic social networking features using graph data structures. This project demonstrates the implementation of a social network using graph theory concepts and data structures.

## Features

- User Management
  - Create user accounts with unique IDs
  - View user profiles
  - Search users by username
  - Display all registered users

- Friend System
  - Send friend requests
  - Accept/reject friend requests
  - View mutual friends
  - Display friend list

## Technical Details

- Implemented using Graph data structure
- Uses adjacency matrix for friend connections
- Handles friend requests using dynamic arrays
- Maximum friend requests limit: 100 per user
- Memory efficient implementation using dynamic memory allocation

## Current Folder Structure

- `README.md`: Contains the documentation for the project.
- `Social-media-project.c`: The main C file containing the implementation of the social media application.

## How to Use

1. Compile the program:
   ```bash
   gcc Social-media-project.c -o social_media
   ```

2. Run the executable:
   ```bash
   ./social_media
   ```

3. Menu Options:
   - 1: Create ID - Register new users
   - 2: View all Users - Display all registered users
   - 3: View Profile - View your profile and handle friend requests
   - 4: Send Friend Request - Send friend requests to other users
   - 5: View Mutuals - Check mutual friends with another user
   - 6: Search by Username - Find users by their username
   - 7: Exit - Log out from the application

## Requirements

- C compiler (GCC recommended)
- Standard C libraries
- Operating System: Windows/Linux/MacOS

## Implementation Details

The application uses the following key data structures:
- Graph structure for managing user connections
- Adjacency matrix for efficient friend relationship storage
- Dynamic arrays for managing friend requests
- String manipulation for user name handling

## Security Features

- Unique user IDs for identification
- Private user ID system
- Secure friend request management
- Input validation for user interactions

## Note

- Keep your user ID private for security purposes
- Friend requests must be accepted/rejected when viewing your profile
- The application maintains a simple text-based interface
- Maximum of 100 pending friend requests per user

## Author

Sunil Kumar P
