# deck means poker card set

import emoji

class Card():
    def __init__(self, suit: str, rank: str) -> None:
        self.suit = suit
        self.rank = rank

    def __str__(self) -> str:
        return f"{self.rank} of {self.suit}"

    def emojize(self) -> str:
        suit = "spade_suit"
        
        if self.suit == "Hearts":
            suit = "heart_suit"
        elif self.suit == "Diamonds":
            suit = "diamond_suit"
        else:
            suit = "club_suit"
        
        return emoji.emojize(f":{suit}: {self.rank}")

def create_deck() -> list:
    suits = ("Hearts", "Spaders", "Clubs", "Diamonds")
    ranks = ("2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace")
    return [Card(suit, rank) for suit in suits for rank in ranks]

def main():
    deck = create_deck()
    for card in deck:
        print(card)

if __name__ == "__main__":
    main()