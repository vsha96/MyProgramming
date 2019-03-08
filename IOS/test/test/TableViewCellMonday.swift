//
//  TableViewCellMonday.swift
//  test
//
//  Created by Shulyugin on 12.12.16.
//  Copyright © 2016 Shulyugin. All rights reserved.
//

import UIKit

class TableViewCellMonday: UITableViewCell {
    @IBOutlet weak var LabelNameMonday: UILabel!
    @IBOutlet weak var LabelTimeMonday: UILabel!
    @IBOutlet weak var LabelNameTuesday: UILabel!
    @IBOutlet weak var LabelTimeTuesday: UILabel!
    @IBOutlet weak var LabelNameWednesday: UILabel!
    @IBOutlet weak var LabelTimeWednesday: UILabel!
    @IBOutlet weak var LabelNameThursday: UILabel!
    @IBOutlet weak var LabelTimeThursday: UILabel!
    @IBOutlet weak var LabelNameFriday: UILabel!
    @IBOutlet weak var LabelTimeFriday: UILabel!
    @IBOutlet weak var LabelNameSaturday: UILabel!
    @IBOutlet weak var LabelTimeSaturday: UILabel!

    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
