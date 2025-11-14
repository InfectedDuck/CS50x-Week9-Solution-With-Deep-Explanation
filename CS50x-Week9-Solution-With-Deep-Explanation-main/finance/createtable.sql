-- Create a table to store transaction history
CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,  -- Unique identifier for each transaction, automatically generated
    user_id VARCHAR(255) NOT NULL,  -- User ID associated with the transaction (cannot be NULL)
    symbol VARCHAR(255) NOT NULL,  -- Stock symbol involved in the transaction (cannot be NULL)
    date DATE NOT NULL,  -- Date of the transaction (cannot be NULL)
    shares INTEGER NOT NULL,  -- Number of shares bought or sold (cannot be NULL)
    price INTEGER NOT NULL,  -- Price per share at the time of the transaction (cannot be NULL)
    total_cost INTEGER NOT NULL,  -- Total cost of the transaction (calculated as shares * price) (cannot be NULL)
    action TEXT NOT NULL CHECK(action IN ('buy', 'sell'))  -- Action type (either 'buy' or 'sell'), must match one of the allowed values
);

-- Create a table to store information about stocks owned by users
CREATE TABLE stocks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,  -- Unique identifier for each stock record, automatically generated
    user_id VARCHAR(255) NOT NULL,  -- User ID associated with the stock record (cannot be NULL)
    symbol VARCHAR(255) NOT NULL,  -- Stock symbol (cannot be NULL)
    shares INTEGER NOT NULL,  -- Number of shares owned by the user (cannot be NULL)
    price INTEGER NOT NULL,  -- Price per share of the stock (cannot be NULL)
    total_cost INTEGER NOT NULL,  -- Total cost of the shares owned (calculated as shares * price) (cannot be NULL)
    UNIQUE(user_id, symbol)  -- Ensure that each user can only have one record per stock symbol
);
