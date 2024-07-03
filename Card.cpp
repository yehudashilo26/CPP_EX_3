#include "Card.hpp"

namespace ariel
{
    CardType Card::getType()
    {
        return type;
    }

    ostream &operator<<(ostream &os, const Card &card)
    {
        switch (card.type)
        {
        case CardType::NONE:
            os << "NONE";
            break;
        case CardType::WHEAT:
            os << "WHEAT";
            break;
        case CardType::WOOD:
            os << "WOOD";
            break;
        case CardType::BRICK:
            os << "BRICK";
            break;
        case CardType::SHEEP:
            os << "SHEEP";
            break;
        case CardType::ORE:
            os << "ORE";
            break;
        case CardType::KNIGHT:
            os << "KNIGHT";
            break;
        case CardType::VICTORY_POINT:
            os << "VICTORY_POINT";
            break;
        case CardType::ROAD_BUILDING:
            os << "ROAD_BUILDING";
            break;
        case CardType::MONOPOLY:
            os << "MONOPOLY";
            break;
        case CardType::YEAR_OF_PLENTY:
            os << "YEAR_OF_PLENTY";
            break;
        case CardType::BIGGEST_ARMY:
            os << "BIGGEST_ARMY";
            break;
        case CardType::LONGEST_ROAD:
            os << "LONGEST_ROAD";
            break;
        default:
            os << "NONE";
        }
        return os;
    }

    string Card::cardTypeToString(CardType type)
    {
        string str;
        switch (type)
        {
        case CardType::WHEAT:
            str = "Wheat";
            break;
        case CardType::WOOD:
            str = "Wood";
            break;
        case CardType::BRICK:
            str = "Brick";
            break;
        case CardType::SHEEP:
            str = "Sheep";
            break;
        case CardType::ORE:
            str = "Ore";
            break;
        case CardType::KNIGHT:
            str = "Knight";
            break;
        case CardType::VICTORY_POINT:
            str = "Victory Point";
            break;
        case CardType::ROAD_BUILDING:
            str = "Road Building";
            break;
        case CardType::MONOPOLY:
            str = "Monopoly";
            break;
        case CardType::YEAR_OF_PLENTY:
            str = "Year of Plenty";
            break;
        default:
            str = "None";
            break;
        }
        return str;
    }
    ostream &operator<<(ostream &os, const CardType type)
    {
        string str;
        switch (type)
        {
        case CardType::WHEAT:
            str = "Wheat";
            break;
        case CardType::WOOD:
            str = "Wood";
            break;
        case CardType::BRICK:
            str = "Brick";
            break;
        case CardType::SHEEP:
            str = "Sheep";
            break;
        case CardType::ORE:
            str = "Ore";
            break;
        case CardType::KNIGHT:
            str = "Knight";
            break;
        case CardType::VICTORY_POINT:
            str = "Victory Point";
            break;
        case CardType::ROAD_BUILDING:
            str = "Road Building";
            break;
        case CardType::MONOPOLY:
            str = "Monopoly";
            break;
        case CardType::YEAR_OF_PLENTY:
            str = "Year of Plenty";
            break;
        default:
            str = "None";
            break;
        }
        os << str;
        return os;
    }

    ResourceCard::ResourceCard(CardType type) : Card(type)
    {
        if (type == CardType::WHEAT || type == CardType::WOOD || type == CardType::BRICK || type == CardType::SHEEP || type == CardType::ORE)
        {
            this->type = type;
        }
        else
        {
            throw invalid_argument("Resource card type must be one of the following: Wheat, Wood, Brick, Sheep, Ore");
        }
    }

    DevelopmentCard::DevelopmentCard(CardType type) : Card(type)
    {
        if (type == CardType::KNIGHT || type == CardType::VICTORY_POINT || type == CardType::ROAD_BUILDING || type == CardType::MONOPOLY || type == CardType::YEAR_OF_PLENTY || type == CardType::BIGGEST_ARMY || type == CardType::LONGEST_ROAD)
        {
            this->type = type;
        }
        else
        {
            throw invalid_argument("Development card type must be one of the following: Knight, Victory Point, Road Building, Monopoly, Year of Plenty, Biggest Army, Longest Road");
        }
        
    }

    void KnightCard::activate()
    {
        cout << "Knight card activated" << endl;
    }

    void VictoryPointCard::activate()
    {
        cout << "Victory Point card activated" << endl;
    }

    void RoadBuildingCard::activate()
    {
        cout << "Road Building card activated" << endl;
    }

    void MonopolyCard::activate()
    {
        cout << "Monopoly card activated" << endl;
    }

    void YearOfPlentyCard::activate()
    {
        cout << "Year of Plenty card activated" << endl;
    }

    Deck::Deck()
    {
        developmentCardsCount[CardType::KNIGHT] = FIVE;
        developmentCardsCount[CardType::VICTORY_POINT] = FIVE;
        developmentCardsCount[CardType::ROAD_BUILDING] = THREE;
        developmentCardsCount[CardType::MONOPOLY] = THREE;
        developmentCardsCount[CardType::YEAR_OF_PLENTY] = THREE;

        for (size_t i = 0; i < developmentCardsCount[CardType::KNIGHT]; i++)
        {
            developmentCards.push_back(new KnightCard());
        }

        for (size_t i = 0; i < developmentCardsCount[CardType::VICTORY_POINT]; i++)
        {
            developmentCards.push_back(new VictoryPointCard());
        }

        for (size_t i = 0; i < developmentCardsCount[CardType::ROAD_BUILDING]; i++)
        {
            developmentCards.push_back(new RoadBuildingCard());
        }

        for (size_t i = 0; i < developmentCardsCount[CardType::MONOPOLY]; i++)
        {
            developmentCards.push_back(new MonopolyCard());
        }

        for (size_t i = 0; i < developmentCardsCount[CardType::YEAR_OF_PLENTY]; i++)
        {
            developmentCards.push_back(new YearOfPlentyCard());
        }

        random_shuffle(developmentCards.begin(), developmentCards.end());
    }

    Deck::~Deck()
    {
        for (DevelopmentCard *card : developmentCards)
        {
            delete card;
        }
    }

    void Deck::addCard(DevelopmentCard *card)
    {
        developmentCards.push_back(card);
    }

    DevelopmentCard *Deck::draw()
    {
        if (developmentCards.empty())
        {
            throw invalid_argument("No more development cards in the deck");
        }
        DevelopmentCard *card = developmentCards.back();
        developmentCards.pop_back();
        return card;
    }

    Player *BiggestArmyCard::getPlayer()
    {
        return player;
    }

    void BiggestArmyCard::setPlayer(Player *player)
    {
        this->player = player;
    }

    void BiggestArmyCard::activate()
    {
        cout << "Biggest Army card activated" << endl;
    }

    Player *LongestRoadCard::getPlayer()
    {
        return player;
    }

    void LongestRoadCard::setPlayer(Player *player)
    {
        this->player = player;
    }

    void LongestRoadCard::activate()
    {
        cout << "Longest Road card activated" << endl;
    }
    
};