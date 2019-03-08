//
//  TimetableViewCell.swift
//  prototype
//
//  Created by Shulyugin on 07.12.16.
//  Copyright © 2016 Shulyugin. All rights reserved.
//

import UIKit

class TimetableViewCell: UITableViewCell {
    @IBOutlet weak var LabelName: UILabel!
    @IBOutlet weak var LabelTime: UILabel!

    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
