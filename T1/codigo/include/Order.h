//
// Created by franc on 12/04/2022.
//

#ifndef DA_T1_ORDER_H
#define DA_T1_ORDER_H

/**
 * This class represents the clients' orders in this project. Orders are represented by a volume, weight, reward and delivery duration.
 */
class Order {
    unsigned volume;
    unsigned weight;
    unsigned reward;
    unsigned duration;
    bool assigned{};
public:
    /**
     * Class constructor with 3 unsigned objects
     * @param volume Orders' volume
     * @param weight Orders' weight
     * @param reward Orders' reward
     * @param duration Orders' duration
     */
    Order(unsigned volume, unsigned weight, unsigned reward, unsigned duration);

    /**
     * Class destructor to clear the object in memory
     */
    ~Order();

    /**
     * Returns orders' volume
     * @return Volume parameter
     */
    unsigned getVolume() const;

    /**
     * Returns orders' weight
     * @return Weight parameter
     */
    unsigned getWeight() const;

    /**
     * Returns orders' reward
     * @return Reward parameter
     */
    unsigned getReward() const;

    /**
     * Returns orders' duration
     * @return Duration parameter
     */
    unsigned getDuration() const;

    /**
     * Returns assigned value. If order has been processed (true) or not (false)
     * @return True or false
     */
    bool getAssignedValue() const;

    /**
     * Updated assigned value to true or false if order has been processed or not
     * @param value true or false
     */
    void setAssignedValue(bool value);
};


#endif //DA_T1_ORDER_H
