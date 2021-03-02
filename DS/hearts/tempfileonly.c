
//////////////////////////////////////////////////////////////////////////////////////////
    switch(suit)
    {
        case HEARTS:
        if(heartsNum > 0)
        {
            /*throw last heart card*/
            VectorDelete(_hand->m_heartsVector, &thrownCardIndex);
            /*add this card to table*/
            VectorAdd(_table, thrownCardIndex);
            break;
        }
        else if(spadesNum > 0)
        {
            /*throw last spades card*/
            VectorDelete(_hand->m_spadesVector, &thrownCardIndex);
            /*add this card to table*/
            VectorAdd(_table, thrownCardIndex);
            break;
        }
        else if(diamondsNum >0)
        {
            /*throw last diamond card*/
            VectorDelete(_hand->m_diamondsVector, &thrownCardIndex);
            /*add this card to table*/
            VectorAdd(_table, thrownCardIndex);
            break;
        }
        else
        {
            /*throw last clubs card*/
            VectorDelete(_hand->m_clubsVector, &thrownCardIndex);
            /*add this card to table*/
            VectorAdd(_table, thrownCardIndex);
            break;
        }
        /*********************************************************************/
        case SPADES:
        if(spadesNum > 0)
        {
            /*throw last spades card*/
            VectorDelete(_hand->m_spadesVector, &thrownCardIndex);
            /*add this card to table*/
            VectorAdd(_table, thrownCardIndex);
            break;
        }
        else if(heartsNum > 0)
        {
            /*throw last heart card*/
            VectorDelete(_hand->m_heartsVector, &thrownCardIndex);
            /*add this card to table*/
            VectorAdd(_table, thrownCardIndex);
            break;
        }
        else if(diamondsNum >0)
        {
            /*throw last diamond card*/
            VectorDelete(_hand->m_diamondsVector, &thrownCardIndex);
            /*add this card to table*/
            VectorAdd(_table, thrownCardIndex);
            break;
        }
        else
        {
            /*throw last clubs card*/
            VectorDelete(_hand->m_clubsVector, &thrownCardIndex);
            /*add this card to table*/
            VectorAdd(_table, thrownCardIndex);
            break;
        }
        /*********************************************************************/
    }


    //////////////////////////////////////////////////////////////////////////////////////
        /*
    size_t i, heartsNum, spadesNum, diamondsNum, clubsNum;
    VectorItemsNum(_hand->m_heartsVector,&heartsNum);
    VectorItemsNum(_hand->m_spadesVector,&spadesNum);
    VectorItemsNum(_hand->m_diamondsVector,&diamondsNum); 
    VectorItemsNum(_hand->m_clubsVector,&clubsNum);
    if(NULL == _hand)
    {
        return ERR_NOT_INITIALIZED;
    }
    if(NULL == _cardsArr)
    {
        return ERR_GENERAL;
    }*/
    /*first i will throw the higest cards of suit hearts, spades, diamonds*/
    /*later, we can modify this function*/
    /*the assumption here that vectors are sorted in ascending order*/
    /*i must check that vectors have at least 1 card*/
    /*
    if(diamondsNum == 0)
    {
            
    }
    else if(heartsNum == 0)
    {

    }
    else if(spadesNum == 0)
    {

    }
    else if ()
    {

    }
    else
    {

    }*/