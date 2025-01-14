package main

import (
	"context"
	"fmt"
	"log"
	"net/http"

	"github.com/gorilla/handlers"
	"github.com/jackc/pgx/v4"
)

// Function to handle player login
func playerLogin(w http.ResponseWriter, r *http.Request) {
	log.Println("Received player login request")

	username := r.URL.Query().Get("username")
	if username == "" {
		http.Error(w, "Username is required", http.StatusBadRequest)
		return
	}

	log.Printf("Player login request for: %s\n", username)

	player, err := getPlayerDetails(username)
	if err != nil {
		log.Printf("Error fetching player details: %v", err)
		http.Error(w, "Failed to fetch player details", http.StatusInternalServerError)
		return
	}

	log.Printf("Player details fetched: %+v\n", player)
	fmt.Fprintf(w, "Player: %s, Email: %s, DisplayName: %s\n", player.Username, player.Email, player.DisplayName)
}

// Function to handle player registration
func playerRegister(w http.ResponseWriter, r *http.Request) {
	log.Println("Received player registration request")

	// Get the player details from the request
	username := r.URL.Query().Get("username")
	email := r.URL.Query().Get("email")
	displayName := r.URL.Query().Get("display_name")

	// Check if all fields are provided
	if username == "" || email == "" || displayName == "" {
		http.Error(w, "All fields (username, email, display_name) are required", http.StatusBadRequest)
		return
	}

	// Register the player in the database
	err := registerPlayer(username, email, displayName)
	if err != nil {
		log.Printf("Error registering player: %v", err)
		http.Error(w, "Failed to register player", http.StatusInternalServerError)
		return
	}

	// Respond with success message
	fmt.Fprintf(w, "Player %s registered successfully\n", username)
}

// Player structure to hold the player details
type Player struct {
	Username    string
	Email       string
	DisplayName string
}

// Function to get player details from the database
func getPlayerDetails(username string) (*Player, error) {
	connString := "postgres://postgres:Persona9797@localhost:5432/game_data"

	conn, err := pgx.Connect(context.Background(), connString)
	if err != nil {
		log.Printf("Unable to connect to database: %v\n", err)
		return nil, err
	}
	defer conn.Close(context.Background())

	var player Player
	sql := `SELECT username, email, display_name FROM accounts WHERE username=$1`
	err = conn.QueryRow(context.Background(), sql, username).Scan(&player.Username, &player.Email, &player.DisplayName)
	if err != nil {
		log.Printf("Error querying player details: %v\n", err)
		return nil, err
	}

	return &player, nil
}

// Function to register a new player in the database
func registerPlayer(username, email, displayName string) error {
	connString := "postgres://postgres:Persona9797@localhost:5432/game_data"

	conn, err := pgx.Connect(context.Background(), connString)
	if err != nil {
		log.Printf("Unable to connect to database: %v\n", err)
		return err
	}
	defer conn.Close(context.Background())

	// Insert the player details into the database
	sql := `INSERT INTO accounts (username, email, display_name) VALUES ($1, $2, $3)`
	_, err = conn.Exec(context.Background(), sql, username, email, displayName)
	if err != nil {
		log.Printf("Error inserting player into database: %v\n", err)
		return err
	}

	return nil
}

func main() {
	http.HandleFunc("/login", playerLogin)
	http.HandleFunc("/register", playerRegister)

	// Enable CORS for all domains (you can customize this for specific domains)
	cors := handlers.CORS(
		handlers.AllowedOrigins([]string{"*"}),            // Allow all origins (use specific domains if needed)
		handlers.AllowedMethods([]string{"GET", "POST"}),  // Allow only GET and POST methods
		handlers.AllowedHeaders([]string{"Content-Type"}), // Allow Content-Type header
	)

	// Wrap your HTTP server with CORS middleware
	log.Println("Server starting on port 8080...")
	log.Fatal(http.ListenAndServe(":8080", cors(http.DefaultServeMux)))
}
