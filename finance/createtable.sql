CREATE TABLE transactions(
id INTEGER PRIMARY KEY AUTOINCREMENT,
user_id VARCHAR(255) NOT NULL,
symbol VARCHAR(255) NOT NULL,
date DATE NOT NULL,
shares INTEGER NOT NULL,
price INTEGER NOT NULL,
total_cost INTEGER NOT NULL,
action TEXT NOT NULL CHECK(action IN ('buy','sell'))
);
CREATE TABLE stocks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id VARCHAR(255) NOT NULL,
    symbol VARCHAR(255) NOT NULL,
    shares INTEGER NOT NULL,
    price INTEGER NOT NULL,
    total_cost INTEGER NOT NULL,
    UNIQUE(user_id, symbol) 
);
